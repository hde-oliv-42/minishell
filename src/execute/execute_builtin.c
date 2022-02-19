/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/03 20:32:53 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtins/builtins.h"

int	is_builtin(t_data *data)
{
	char	*program_name;

	program_name = ((t_string *)data->program->name)->value;
	if (program_name == NULL)
		return (0);
	else if (!ft_strncmp(program_name, "cd", 3))
		return (1);
	else if (!ft_strncmp(program_name, "echo", 5))
		return (2);
	else if (!ft_strncmp(program_name, "export", 7))
		return (3);
	else if (!ft_strncmp(program_name, "unset", 6))
		return (4);
	else if (!ft_strncmp(program_name, "env", 4))
		return (5);
	else if (!ft_strncmp(program_name, "pwd", 4))
		return (6);
	else if (!ft_strncmp(program_name, "exit", 5))
		return (7);
	return (0);
}

static void	capeta(t_data *data, int id)
{
	if (id == 1)
		*(data->wstatus) = cd(data->program, g_env);
	else if (id == 2)
		*(data->wstatus) = echo(data->program);
	else if (id == 3)
		*(data->wstatus) = export(data->program, &g_env);
	else if (id == 4)
		*(data->wstatus) = unset(data->program, &g_env);
	else if (id == 5)
		*(data->wstatus) = env(g_env);
	else if (id == 6)
		*(data->wstatus) = pwd();
	else if (id == 7)
		*(data->wstatus) = ms_exit(data->program, data);
	else
		*(data->wstatus) = 0;
}

void	restore_fd(t_data *data)
{
	if (dup2(data->og_fd[0], STDIN_FILENO) < 0)
		flush_minishell(data);
	if (dup2(data->og_fd[1], STDOUT_FILENO) < 0)
		flush_minishell(data);
}

int	execute_builtin(t_data *data, int id)
{
	if (id == 0)
		return (-1);
	check_if_must_open_stdin(data, 0);
	check_if_must_open_stdout(data, 0);
	open_all_input_files(data);
	open_all_output_files(data);
	capeta(data, id);
	restore_fd(data);
	data->last_program = data->program;
	data->program = data->program->next;
	return (*(data->wstatus));
}
