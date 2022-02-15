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
#include "builtins/builtins.h"
#include "libft.h"

char **g_env = NULL;

int	is_builtin(t_data *data)
{
	if (data->program->name == NULL)
		return (0);
	else if (!ft_strncmp(data->program->name, "cd", 3))
		return (1);
	else if (!ft_strncmp(data->program->name, "echo", 5))
		return (2);
	else if (!ft_strncmp(data->program->name, "export", 7))
		return (3);
	else if (!ft_strncmp(data->program->name, "unset", 6))
		return (4);
	else if (!ft_strncmp(data->program->name, "env", 4))
		return (5);
	else if (!ft_strncmp(data->program->name, "pwd", 4))
		return (6);
	return (0);
}

int	execute_builtin(t_data *data, int id)
{
	if (id == 0)
		return (-1);
	if (id == 1)
	{
		if (cd(data->program, g_env))
			*(data->wstatus) = 1;
	}
	else if (id == 2)
	{
		if (echo(data->program))
			*(data->wstatus) = 1;
	}
	else if (id == 3)
	{
		if (export(data->program, &g_env))
			*(data->wstatus) = 1;
	}
	else if (id == 4)
	{
		if (unset(data->program, &g_env))
			*(data->wstatus) = 1;
	}
	else if (id == 5)
		env(g_env);
	else if (id == 6)
	{
		if (pwd())
			*(data->wstatus) = 1;
	}
	else
		*(data->wstatus) = 0;
	data->last_program = data->program;
	data->program = data->program->next;
	return (*(data->wstatus));
}

void	execute_one_command(t_data *data)
{
	char	*path;
	char	**argv;

	path = NULL;
	path = find_path(data->program->name, g_env);
	if (path == NULL)
	{
		command_not_found(data->program->name);
		*(data->wstatus) = 1;
		free_minishell(data);
		exit(1);
	}
	else
	{
		child_handlers();
		argv = generate_argv_array(data->program);
		check_pipe_relations(data);
		execve(path, argv, g_env);
		// TODO: Handle execve errors
	}
}

void	execute(t_program *program_list)
{
	t_data	data;
	int		id;
	int		wstatus;

	if (g_env == NULL)
		initialize_ms_env(&g_env);
	wstatus = 0;
	data = (t_data){ program_list, program_list, NULL, 0, &wstatus };
	while (data.program)
	{
		if (execute_builtin(&data, is_builtin(&data)) != -1)
			continue ;
		if (data.program->next_relation == PIPE)
			if (pipe(data.program->next_pipe))
				break ;
		if (check_conditional_error(&data))
			break;
		id = fork();
		if (id == 0)
			handle_child(&data);
		else if (id < 0)
			break ;
		else
		{
			if (data.program->next_relation == AND || data.program->next_relation == OR)
				handle_conditional_wait(&data);
			else
				data.program_count++;
			if (data.last_program && data.last_program->next_relation == PIPE)
				close_pipe(data.last_program->next_pipe, &data);
			data.last_program = data.program;
			data.program = data.program->next;
		}
	}
	// TODO: Check ERRNO and print any errors
	ignore_signals();
	handle_wait(&data);
	handle_signals();
	// Free data
}
