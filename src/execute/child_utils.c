/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:37 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "ft_printf/libftprintf.h"
#include "parsing/parsing.h"
#include <unistd.h>

void	check_if_must_open_stdin(t_data *data, int is_child)
{
	if (data->last_program && data->last_program->next_relation == PIPE)
	{
		if (dup2(data->last_program->next_pipe[0], STDIN_FILENO) < 0)
			flush_minishell(data);
		if (is_child)
		{
			if (close(data->last_program->next_pipe[0]))
				flush_minishell(data);
		}
	}
}

void	check_if_must_open_stdout(t_data *data, int is_child)
{
	if (!data->program->output_list && data->program->next_relation == PIPE)
	{
		if (dup2(data->program->next_pipe[1], STDOUT_FILENO) < 0)
			flush_minishell(data);
		if (is_child)
		{
			if (close(data->program->next_pipe[1]))
				flush_minishell(data);
		}
	}
}

void	open_all_output_files(t_data *data)
{
	t_list			*files_out;
	t_redirection	*file_out;
	int				out_fd;

	files_out = data->program->output_list;
	while (files_out)
	{
		file_out = files_out->content;
		out_fd = open(file_out->file_name, \
						O_CREAT | O_WRONLY | file_out->type, \
						0644);
		if (!is_writable(file_out->file_name))
			flush_minishell(data);
		if (out_fd == -1)
			flush_minishell(data);
		if (dup2(out_fd, 1) < 0)
			flush_minishell(data);
		files_out = files_out->next;
		if (close(out_fd))
			flush_minishell(data);
	}
}

// TODO: Check if this works later
static void	handle_heredoc(
	t_data *data, t_list **files_in, t_redirection *file_in)
{
	int		fd[2];

	*files_in = (*files_in)->next;
	if (pipe(fd) == -1)
	{
		perror("heredoc");
		flush_minishell(data);
	}
	dup2(fd[0], STDIN_FILENO);
	ft_dprintf(fd[1], "%s", file_in->contents);
	close(fd[0]);
	close(fd[1]);
}

void	open_all_input_files(t_data *data)
{
	t_list			*files_in;
	t_redirection	*file_in;
	int				in_fd;

	files_in = data->program->input_list;
	while (files_in)
	{
		file_in = files_in->content;
		if (file_in->type == RD_HERE_DOC)
			handle_heredoc(data, &files_in, file_in);
		else
		{
			in_fd = open(file_in->file_name, file_in->type);
			if (!is_readable(file_in->file_name))
				flush_minishell(data);
			if (in_fd == -1)
				flush_minishell(data);
			if (dup2(in_fd, 0) < 0)
				flush_minishell(data);
			files_in = files_in->next;
			if (close(in_fd))
				flush_minishell(data);
		}
	}
}
