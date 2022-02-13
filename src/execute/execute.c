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
		// free_minishell();
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

void	execute(t_program *program_list)
{
	int				wstatus;
	t_program		*program;
	t_program		*last_program;
	int				id;
	int				program_count;

	if (g_env == NULL)
		initialize_ms_env(&g_env);
	program = program_list;
	last_program = NULL;
	wstatus = 0;
	program_count = 0;
	ignore_signals();
	while (program)
	{
		if (program->next_relation == PIPE)
			if (pipe(program->next_pipe))
				break ;
		if (check_conditional_error(last_program, wstatus))
			break;
		id = fork();
		if (id == 0)
			handle_child(last_program, program, wstatus);
		else if (id < 0)
			break ;
		else
		{
			if (program->next_relation == AND || program->next_relation == OR)
				handle_conditional_wait(&wstatus);
			else
				program_count++;
			if (last_program && last_program->next_relation == PIPE)
				close_pipe(last_program->next_pipe);
			last_program = program;
			program = program->next;
		}
	}
	// TODO: Check ERRNO if and print any errors
	handle_wait(program_list, &wstatus);
	handle_signals();
}
