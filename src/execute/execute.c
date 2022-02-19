/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/18 19:36:27 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expand/expand.h"

char	**g_env = NULL;

void	execute_one_command(t_data *data)
{
	char	*path;
	char	*program_name;
	char	**argv;

	program_name = ((t_string *)data->program->name)->value;
	path = find_path(program_name, g_env);
	if (path == NULL)
	{
		command_not_found(program_name);
		*(data->wstatus) = 1;
		destroy_pipeline(data->program_list);
		ft_dfree(g_env);
		close(data->og_fd[0]);
		close(data->og_fd[1]);
		exit(127);
	}
	else if (!is_executable(path))
		flush_minishell(data);
	else
	{
		reset_child_signals();
		argv = generate_argv_array(data->program);
		check_pipe_relations(data);
		execve(path, argv, g_env);
		flush_minishell(data);
	}
}

static void	handle_parent(t_data *data)
{
	if (data->program->next_relation == AND || \
		data->program->next_relation == OR)
		handle_conditional_wait(data);
	else
		data->program_count++;
	if (data->last_program && data->last_program->next_relation == PIPE)
		close_pipe(data->last_program->next_pipe, data);
	if (data->must_continue == 0)
		data->program = NULL;
	else
	{
		data->last_program = data->program;
		data->program = data->program->next;
	}
}

void	execute_loop(t_data *data)
{
	int		id;

	while (data->must_continue && data->program)
	{
		expand_program(data->program, data);
		if (data->program->next_relation == PIPE)
			if (pipe(data->program->next_pipe))
				break ;
		if (execute_builtin(data, is_builtin(data)) != -1)
			continue ;
		if (check_conditional_error(data))
			break ;
		id = fork();
		if (id == 0)
			handle_child(data);
		else if (id < 0)
			break ;
		else
			handle_parent(data);
	}
}

void	execute(t_data *data, t_program *program_list)
{
	if (g_env == NULL)
		initialize_ms_env(&g_env);
	data->og_fd[0] = dup(STDIN_FILENO);
	data->og_fd[1] = dup(STDOUT_FILENO);
	data->program_list = program_list;
	data->program = program_list;
	data->last_program = NULL;
	data->program_count = 0;
	execute_loop(data);
	if (errno)
		perror("execute");
	ignore_signals();
	handle_wait(data);
	close_pipe(data->og_fd, data);
	handle_signals();
}
