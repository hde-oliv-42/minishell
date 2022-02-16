/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/14 21:03:24 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	check_conditional_error(t_data *data)
{
	if (data->last_program && \
		data->last_program->next_relation == AND && *(data->wstatus) != 0)
		return (1);
	else if (data->last_program \
			&& data->last_program->next_relation == OR \
			&& *(data->wstatus) == 0)
		return (1);
	return (0);
}

void	handle_wait(t_data *data)
{
	int			size;
	int			status;
	int			wait_result;

	size = data->program_count;
	while (size)
	{
		wait_result = wait(&status);
		if (wait_result == -1 && errno == EINTR)
			continue ;
		size--;
		if (WIFEXITED(status))
			*(data->wstatus) = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*(data->wstatus) = WTERMSIG(status) + 128;
		else if (WIFSIGNALED(status))
			*(data->wstatus) = WSTOPSIG(status) + 128;
		else
			*(data->wstatus) = 0;
	}
}

void	handle_conditional_wait(t_data *data)
{
	int	waifu;
	int	status;

	wait(&status);
	waifu = WIFEXITED(status);
	if (waifu)
		*(data->wstatus) = WEXITSTATUS(status);
	else
		*(data->wstatus) = 1;
}

void	handle_child(t_data *data)
{
	check_if_must_open_stdin(data);
	check_if_must_open_stdout(data);
	open_all_input_files(data);
	open_all_output_files(data);
	execute_one_command(data);
}
