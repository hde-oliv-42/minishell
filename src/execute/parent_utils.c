/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:57 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "structures.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void	cancel_all_pipe_commands(t_data *data)
{
	while (data->program && \
		(data->program->next_relation == PIPE || \
		data->last_program->next_relation == PIPE))
	{
		data->program->ret = data->last_program->ret;
		data->last_program = data->program;
		data->program = data->program->next;
	}
}

int	check_conditional_error(t_data *data)
{
	if (data->last_program && \
		data->last_program->next_relation == AND && \
		data->wstatus != 0)
		return (1);
	else if (data->last_program \
			&& data->last_program->next_relation == OR \
			&& data->wstatus == 0)
		return (1);
	return (0);
}

void	set_status_code(int wait_pid, int status, t_data *data)
{
	t_program	*program;

	program = data->program_list;
	while (program)
	{
		if (program->pid == wait_pid)
		{
			program->ret = status;
			break ;
		}
		program = program->next;
	}
	data->wstatus = status;
}

void	handle_child(t_data *data)
{
	check_if_must_open_stdin(data, 1);
	check_if_must_open_stdout(data, 1);
	open_all_input_files(data);
	open_all_output_files(data);
	execute_one_command(data);
}
