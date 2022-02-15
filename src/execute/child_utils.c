/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/03 20:32:53 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	check_if_must_open_stdin(t_data *data)
{
	if (data->last_program && data->last_program->next_relation == PIPE)
	{
		if (dup2(data->last_program->next_pipe[0], STDIN_FILENO) < 0)
			flush_minishell(data);
		if (close(data->last_program->next_pipe[0]))
			flush_minishell(data);
	}
}

void	check_if_must_open_stdout(t_data *data)
{
	if (!data->program->output_list && data->program->next_relation == PIPE)
	{
		if (dup2(data->program->next_pipe[1], STDOUT_FILENO) < 0)
			flush_minishell(data);
		if (close(data->program->next_pipe[1]))
			flush_minishell(data);
	}
}

void	open_all_output_files(t_data *data, int *out_fd)
{
	t_list			*files_out;
	t_redirection	*file_out;

	files_out = data->program->output_list;
	while (files_out)
	{
		file_out = files_out->content;
		*out_fd = open(file_out->file_name, O_CREAT | O_WRONLY | file_out->type, 0644);
		if (*out_fd == -1)
			flush_minishell(data);
		if (dup2(*out_fd, 1) < 0)
			flush_minishell(data);
		files_out = files_out->next;
		if (close(*out_fd))
			flush_minishell(data);
	}
}

void	open_all_input_files(t_data *data, int out_fd)
{
	t_list			*files_in;
	t_redirection	*file_in;
	int				in_fd;

	files_in = data->program->input_list;
	while (files_in)
	{
		file_in = files_in->content;
		if (file_in->type == RD_HERE_DOC)
		{
			// handle_heredoc();
		}
		else
		{
			in_fd = open(file_in->file_name, file_in->type); // TODO: Check for errors later
			if (in_fd == -1)
				flush_minishell(data);
			if (dup2(out_fd, 0) < 0)
				flush_minishell(data);
			files_in = files_in->next;
			if (close(in_fd))
				flush_minishell(data);
		}
	}
}
