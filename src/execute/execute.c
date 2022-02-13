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

static char **g_env;

// TODO: Check for builtins
void	execute_one_command(t_program *last_program, t_program *program, int *wstatus)
{
	char	*path;
	char	**argv;
	int		err;

	path = NULL;
	path = find_path(program->name, g_env);
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
		err = execve(path, argv, g_env);
		dprintf(2, "ERR = %d\n", err);
		perror("execve");
	}
}

// NOTE: In conditional executions, WAIT will be needed inside the loop
void	execute(t_program *program_list)
{
	int				wstatus;
	t_program		*program;
	t_program		*last_program;
	int				id;

	if (g_env == NULL)
		initialize_ms_env(&g_env);
	program = program_list;
	last_program = NULL;
	wstatus = 0;
	ignore_signals();
	while (program)
	{
		if (program->next_relation == PIPE)
		{
			pipe(program->next_pipe);
			// Cancel everything on error and return prompt
		}
		id = fork();
		if (id == 0)
			handle_child(last_program, program, wstatus);
		/* else if (id == -1) */
		/* 	// Cancel everything and return prompt */
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
