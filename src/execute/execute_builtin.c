/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:39 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtins/builtins.h"

int	is_builtin(t_data *data)
{
	char	*program_name;

	if (data->program->name == NULL)
		return (0);
	program_name = ((t_string *)data->program->name)->value;
	if (program_name == NULL)
		return (0);
	else if (!ft_strncmp(program_name, "echo", 5))
		return (1);
	else if (!ft_strncmp(program_name, "env", 4))
		return (2);
	else if (!ft_strncmp(program_name, "pwd", 4))
		return (3);
	else if (!ft_strncmp(program_name, "unset", 6))
		return (4);
	else if (!ft_strncmp(program_name, "cd", 3))
		return (5);
	else if (!ft_strncmp(program_name, "export", 7))
		return (6);
	else if (!ft_strncmp(program_name, "exit", 5))
		return (7);
	return (0);
}

static void	execute_one_builtin(t_data *data, int id)
{
	if (id == 1)
		data->program->ret = echo(data->program);
	else if (id == 2)
		data->program->ret = env(data->program, data);
	else if (id == 3)
		data->program->ret = pwd();
	else if (id == 4)
		data->program->ret = unset(data->program, &g_env);
	else if (id == 5)
		data->program->ret = cd(data->program, &g_env);
	else if (id == 6)
		data->program->ret = export(data->program, data);
	else if (id == 7)
		data->program->ret = ms_exit(data->program, data);
	else
		data->program->ret = 0;
}

void	restore_fd(t_data *data)
{
	if (dup2(data->og_fd[0], STDIN_FILENO) < 0)
		flush_minishell(data);
	if (dup2(data->og_fd[1], STDOUT_FILENO) < 0)
		flush_minishell(data);
}

static void	execution_core(t_data *data, int id)
{
	if (data->program->next_relation == PIPE)
		if (pipe(data->program->next_pipe))
			flush_minishell(data);
	check_if_must_open_stdin(data, 0);
	check_if_must_open_stdout(data, 0);
	open_all_input_files(data);
	open_all_output_files(data);
	execute_one_builtin(data, id);
	restore_fd(data);
}

int	execute_builtin(t_data *data, int id)
{
	int	ret;

	if (id == 0)
		return (-1);
	else if (check_conditional_error(data))
	{
		data->program->ret = data->last_program->ret;
		ret = data->last_program->ret;
		data->last_program = data->program;
		data->program = data->program->next;
		return (ret);
	}
	else if (id < 4 || id == 6)
		execution_core(data, id);
	else if (data->last_program && data->last_program->next_relation != PIPE)
		execution_core(data, id);
	else if (data->program->next_relation != PIPE && !data->last_program)
		execution_core(data, id);
	ret = data->program->ret;
	data->last_program = data->program;
	data->program = data->program->next;
	return (ret);
}
