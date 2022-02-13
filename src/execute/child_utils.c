#include "execute.h"

void	check_if_must_open_stdin(t_program *last_program)
{
	if (last_program && last_program->next_relation == PIPE)
	{
		if (dup2(last_program->next_pipe[0], STDIN_FILENO) < 0)
		{
			// flush_minishell();
		}
		if (close(last_program->next_pipe[0]))
		{
			// flush_minishell();
		}
	}
}

void	check_if_must_open_stdout(t_program *program)
{
	if (!program->output_list && program->next_relation == PIPE)
	{
		if (dup2(program->next_pipe[1], STDOUT_FILENO))
		{
			// flush_minishell();
		}
		if (close(program->next_pipe[1]))
		{
			// flush_minishell();
		}
	}
}

void	open_all_output_files(t_program *program, int *out_fd)
{
	t_list			*files_out;
	t_redirection	*file_out;

	files_out = program->output_list;
	while (files_out)
	{
		file_out = files_out->content;
		*out_fd = open(file_out->file_name, O_CREAT | O_WRONLY | file_out->type, 0644);
		if (*out_fd == -1)
		{
			// flush_minishell();
		}
		if (dup2(*out_fd, 1) < 0)
		{
			// flush_minishell();
		}
		files_out = files_out->next;
		if (close(*out_fd))
		{
			// flush_minishell();
		}
	}
}

void	open_all_input_files(t_program *program, int out_fd)
{
	t_list			*files_in;
	t_redirection	*file_in;
	int				in_fd;

	files_in = program->input_list;
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
			{
				// flush_minishell();
			}
			if (dup2(out_fd, 0) < 0)
			{
				// flush_minishell();
			}
			files_in = files_in->next;
			if (close(in_fd))
			{
				// flush_minishell();
			}
		}
	}
}
