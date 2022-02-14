/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/03 20:32:53 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	check_conditional_error(t_data *data)
{
	if (data->last_program && data->last_program->next_relation == AND && data->wstatus != 0)
		return (1);
	else if (data->last_program && data->last_program->next_relation == OR && data->wstatus == 0)
		return (1);
	return (0);
}

void	handle_wait(t_data *data)
{
	t_program	*tmp;
	int			size;
	int			status;
	int			waifu; // TODO: Change this name later

	tmp = data->program_list;
	size = 0;
	while (tmp)
	{
		if (tmp->next_relation != OR && tmp->next_relation != AND)
			size++;
		tmp = tmp->next;
	}
	while (size)
	{
		wait(&status);
		size--;
		waifu = WIFEXITED(status);
		if (waifu)
			*(data->wstatus) = WEXITSTATUS(status);
		else
			*(data->wstatus) = 1;
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
	int	out_fd;

	out_fd = 0;
	check_if_must_open_stdin(data);
	check_if_must_open_stdout(data);
	open_all_output_files(data, &out_fd);
	open_all_input_files(data, out_fd);
	execute_one_command(data);
}
