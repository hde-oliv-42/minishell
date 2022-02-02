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

void	print_array_of_strings(char **strings)
{
	for (int i = 0; strings[i] != NULL; i++)
		printf("--> %s\n", strings[i]);
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

int	is_builtin(char *name)
{
	if (!ft_strncmp(name, "cd", 2))
		return (1);
	else if (!ft_strncmp(name, "echo", 4))
		return (1);
	else if (!ft_strncmp(name, "env", 3))
		return (1);
	else if (!ft_strncmp(name, "export", 6))
		return (1);
	else if (!ft_strncmp(name, "pwd", 3))
		return (1);
	else if (!ft_strncmp(name, "unset", 5))
		return (1);
	return (0);
}

void	execute_builtin(t_program *program, char **ms_env)
{
	(void)program;
	(void)ms_env;
}

void	execute_one_command(t_program *program, char **ms_env)
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
	else if (program->next_relation == AND || program->next_relation == OR)
		execute_conditionally(program);
	else if (is_builtin(program->name))
		execute_builtin(program, ms_env);
	else
	{
		path = it_exists(program->name, ms_env);
		if (path == NULL)
			command_not_found(program->name);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				argv = generate_argv_array(program);
				// print_array_of_strings(ms_env);
				execve(path, argv, ms_env);
			}
			waitpid(pid, &ret, 0);
		}
	}
}

void	execute(t_program *program_list)
{
	static char	**ms_env;

	if (!ms_env)
	{
		if (initialize_ms_env(&ms_env))
			printf("ERROR\n");
		if (ms_env == NULL)
			(void)ms_env;
			// quit_minishell()
	}
	while (program_list != NULL)
	{
		execute_one_command(program_list, ms_env);
		program_list = program_list->next;
	}
}

