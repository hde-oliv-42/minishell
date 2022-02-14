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
#include "libft.h"

static char **g_env;

// TODO: Check for builtins
void	execute_one_command(t_data *data)
{
	char	*path;
	char	**argv;

	path = NULL;
	path = find_path(data->program->name, g_env);
	if (path == NULL)
	{
		command_not_found(data->program->name);
		*(data->wstatus) = 1;
		free_minishell(data);
		exit(1);
	}
	else
	{
		child_handlers();
		argv = generate_argv_array(data->program);
		check_pipe_relations(data);
		execve(path, argv, g_env);
		// TODO: Handle execve errors
	}
}

void	execute(t_program *program_list)
{
	t_data	data;
	int		id;
	int		wstatus;

	if (g_env == NULL)
		initialize_ms_env(&g_env);
	data = (t_data){ program_list, program_list, NULL, 0, &wstatus };
	ignore_signals();
	while (data.program)
	{
		if (data.program->next_relation == PIPE)
			if (pipe(data.program->next_pipe))
				break ;
		if (check_conditional_error(&data))
			break;
		id = fork();
		if (id == 0)
			handle_child(&data);
		else if (id < 0)
			break ;
		else
		{
			if (data.program->next_relation == AND || data.program->next_relation == OR)
				handle_conditional_wait(&data);
			else
				data.program_count++;
			if (data.last_program && data.last_program->next_relation == PIPE)
				close_pipe(data.last_program->next_pipe, &data);
			data.last_program = data.program;
			data.program = data.program->next;
		}
	}
	// TODO: Check ERRNO and print any errors
	handle_wait(&data);
	handle_signals();
	// Free data
}
