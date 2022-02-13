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
#include "debug/debug.h"
#include "libft.h"
#include "parsing/parsing.h"
#include "signals/signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char **g_env;

void	check_conditional_error(t_program *last_program, int wstatus)
{
	if (last_program && last_program->next_relation == AND && wstatus != 0)
	{
		// free everything
		exit(0);
	}
	else if (last_program && last_program->next_relation == OR && wstatus == 0)
	{
		// free everything
		exit(0);
	}
}

void	check_if_must_open_stdin(t_program *last_program)
{
	if (last_program && last_program->next_relation == PIPE)
	{
		dup2(last_program->next_pipe[0], STDIN_FILENO);
		close(last_program->next_pipe[0]);
	}

}

void	check_if_must_open_stdout(t_program *program)
{
	if (!program->output_list && program->next_relation == PIPE)
	{
		dup2(program->next_pipe[1], STDOUT_FILENO);
		close(program->next_pipe[1]);
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
		dup2(*out_fd, 1);
		files_out = files_out->next;
		close(*out_fd);
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
			in_fd = open(file_in->file_name, file_in->type, 0644); // TODO: Check for errors later
			dup2(out_fd, 0);
			files_in = files_in->next;
			close(in_fd);
		}
	}
}

void	command_not_found(char *program_name)
{
	printf("minishell: %s: command not found\n", program_name);
}


char	**generate_argv_array(t_program *program)
{
	char	**argv;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(program->params) + 1;
	argv = (char **)ft_calloc(size + 1, sizeof(char *));
	argv[i++] = ft_strdup(program->name);
	while (i < size)
	{
		argv[i++] = ft_strdup(program->params->content);
		program->params = program->params->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	check_pipe_relations(t_program *last_program, t_program *program)
{
	if (last_program)
		close(last_program->next_pipe[1]);
	close(program->next_pipe[0]);
	if (last_program && last_program->next_relation != PIPE)
		close(last_program->next_pipe[0]);
	if (program->next_relation != PIPE)
		close(program->next_pipe[1]);
}

// TODO: Check for builtins
void	execute_one_command(t_program *last_program, t_program *program, int *wstatus)
{
	char	*path;
	char	**argv;

	path = NULL;
	path = it_exists(program->name, g_env);
	if (path == NULL)
	{
		command_not_found(program->name);
		*wstatus = 1;
		// Free everything
		exit(1);
	}
	else
	{
		child_handlers();
		argv = generate_argv_array(program);
		check_pipe_relations(last_program, program);
		execve(path, argv, g_env);
	}
}

void	handle_wait(t_program *program_list, int *wstatus)
{
	t_program	*tmp;
	int			size;
	int			status;
	int			waifu; // TODO: Change this name later

	tmp = program_list;
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
			*wstatus = WEXITSTATUS(status);
		else
			*wstatus = 1;
	}
}

void	handle_child(t_program *last_program, t_program *program, int wstatus)
{
	int	out_fd;

	out_fd = 0;
	check_if_must_open_stdin(last_program);
	check_conditional_error(last_program, wstatus);
	check_if_must_open_stdout(program);
	open_all_output_files(program, &out_fd);
	open_all_input_files(program, out_fd);
	execute_one_command(last_program, program, &wstatus);
}

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	handle_parent_wait(int *wstatus)
{
	int	waifu;
	int	status;

	wait(&status);
	waifu = WIFEXITED(status);
	if (waifu)
		*wstatus = WEXITSTATUS(status);
	else
		*wstatus = 1;
}

// NOTE: In conditional executions, WAIT will be needed inside the loop
void	execute(t_program *program_list)
{
	int				wstatus;
	t_program		*program;
	t_program		*last_program;

	if (g_env == NULL)
		initialize_ms_env(&g_env);
	program = program_list;
	last_program = NULL;
	wstatus = 0;
	ignore_signals();
	while (program)
	{
		pipe(program->next_pipe);
		if (fork() == 0)
			handle_child(last_program, program, wstatus);
		else
		{
			if (program->next_relation == AND || program->next_relation == OR)
				handle_parent_wait(&wstatus);
			if (last_program)
				close_pipe(last_program->next_pipe);
			if (!program->next)
				close_pipe(program->next_pipe);
			last_program = program;
			program = program->next;
		}
	}
	handle_wait(program_list, &wstatus);
	handle_signals();
}

// --trace-children=yes --track-fds=yes -s --leak-check=full --show-leak-kinds=all
