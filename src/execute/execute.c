/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/29 20:23:59 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_subcommand(t_program *program)
{
	(void)program;
}

void	execute_pipeliner(t_program *program)
{
	(void)program;
}

void	execute_conditionally(t_program *program)
{
	(void)program;
}

char	*find_path(char *program_name)
{
	return (ft_strjoin("/usr/bin/", program_name));
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
	argv = (char **)malloc(size + 1);
	argv[i++] = program->name;
	while (i < size)
	{
		argv[i++] = program->params->content;
		program->params = program->params->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	execute_one_command(t_program *program)
{
	char	*path;
	char	**argv;
	pid_t	pid;
	int		ret;

	path = NULL;

	if (program->type == SUBSHELL)
		execute_subcommand(program);
	else if (program->next_relation == PIPE)
		execute_pipeliner(program);
	else if (program->next_relation == AND)
		execute_conditionally(program);
	else
	{
		path = find_path(program->name);
		if (path == NULL)
			command_not_found(program->name);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				argv = generate_argv_array(program);
				execve(path, argv, NULL);
				free(argv);
				free(path);
			}
			waitpid(pid, &ret, 0);
		}
	}
}

void	execute(t_program *program_list)
{
	while (program_list != NULL)
	{
		execute_one_command(program_list);
		program_list = program_list->next;
	}
}

