/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/03 20:32:53 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

void	check_pipe_relations(t_data *data)
{
	if (data->last_program && data->last_program->next_relation == PIPE)
	{
		if (close(data->last_program->next_pipe[1]))
			flush_minishell(data);
	}
	if (data->program->next_relation)
	{
		if (close(data->program->next_pipe[0]))
			flush_minishell(data);
	}
}

void	command_not_found(char *program_name)
{
	ft_dprintf(2, "minishell: %s: command not found\n", program_name);
}

void	flush_minishell(t_data *data)
{
	destroy_pipeline(data->program_list);
	ft_dfree(g_env);
	// TODO: Remove this later
	perror("FLUSH");
	exit(errno);
}

void	close_pipe(int fd[2], t_data *data)
{
	if (close(fd[0]))
		flush_minishell(data);
	if (close(fd[1]))
		flush_minishell(data);
}
