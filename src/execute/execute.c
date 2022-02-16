/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/03 20:32:53 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parsing/parsing.h"

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
		exit(1);
	}
	else
	{
		child_handlers();
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
	data->last_program = data->program;
	data->program = data->program->next;
}

// TODO: Check for permissions
void	execute_loop(t_data *data)
{
	int		id;

	while (data->program)
	{
		if (execute_builtin(data, is_builtin(data)) != -1)
			continue ;
		if (data->program->next_relation == PIPE)
			if (pipe(data->program->next_pipe))
				break ;
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

void	execute(t_program *program_list)
{
	t_data	data;
	int		wstatus;

	if (g_env == NULL)
		initialize_ms_env(&g_env);
	wstatus = 0;
	data = (t_data){program_list, program_list, NULL, 0, &wstatus};
	execute_loop(&data);
	if (errno)
		perror("execute");
	ignore_signals();
	handle_wait(&data);
	handle_signals();
}
