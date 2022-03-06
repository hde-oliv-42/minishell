/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/03/06 14:45:51 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	**generate_argv_array(t_program *program)
{
	char	**argv;
	char	*program_name;
	char	*param;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(program->params) + 1;
	argv = (char **)ft_calloc(size + 1, sizeof(char *));
	program_name = ((t_string *)program->name)->value;
	argv[i++] = ft_strdup(program_name);
	while (i < size)
	{
		param = ((t_string *)program->params->content)->value;
		argv[i++] = ft_strdup(param);
		program->params = program->params->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	check_pipe_relations(t_data *data)
{
	if (data->last_program && data->last_program->next_relation == PIPE)
	{
		if (close_fd(data->last_program->next_pipe[1]))
			flush_minishell(data);
	}
	if (data->program->next_relation == PIPE)
	{
		if (close_fd(data->program->next_pipe[0]))
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
	close_fd(data->og_fd[0]);
	close_fd(data->og_fd[1]);
	perror("minishell");
	exit(errno);
}

void	close_pipe(int fd[2], t_data *data)
{
	if (close_fd(fd[0]))
		flush_minishell(data);
	if (close_fd(fd[1]))
		flush_minishell(data);
}
