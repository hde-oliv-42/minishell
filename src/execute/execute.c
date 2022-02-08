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
#include "parsing/parsing.h"
#include "signals/signals.h"
#include <sys/wait.h>
#include <unistd.h>

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

void	execute_subcommand(t_program *program)
{
	(void)program;
}

int	number_of_pipes(t_program *program)
{
	int n_of_pipes;

	n_of_pipes = 0;
	while (program)
	{
		if (program->next_relation == PIPE)
			n_of_pipes++;
		program = program->next;
	}
	return (n_of_pipes);
}

// NOTE: God is dead. And we have killed him.
void	execute_pipeliner(t_program *program, char **ms_env)
{
	int		initial_n_of_pipes;
	int		actual_n_of_pipes;
	int		fd[2];
	int 	id;
	int		tmp_in;
	int		tmp_out;
	char	**argv;
	char	*path;

	initial_n_of_pipes = number_of_pipes(program);
	actual_n_of_pipes = initial_n_of_pipes;
	pipe(fd);
	while (actual_n_of_pipes != 0)
	{
		id = fork();
		if (id == 0)
		{
			path = NULL;
			path = it_exists(program->name, ms_env);
			if (path == NULL)
				command_not_found(program->name);
			if (actual_n_of_pipes == initial_n_of_pipes)
			{
				tmp_out = dup2(fd[1], STDOUT_FILENO);
				child_handlers();
				argv = generate_argv_array(program);
				close(tmp_out);
				close(fd[0]);
				execve(path, argv, ms_env);
				close(fd[1]);
			}
			else
			{
				tmp_out = dup2(fd[1], STDOUT_FILENO);
				tmp_in = dup2(fd[0], STDIN_FILENO);
				child_handlers();
				argv = generate_argv_array(program);
				close(tmp_out);
				close(tmp_in);
				execve(path, argv, ms_env);
				close(fd[0]);
				close(fd[1]);
			}
		}
		ignore_signals();
		waitpid(id, NULL, 0);
		handle_signals();
	}
	id = fork();
	if (id == 0)
	{
		tmp_in = dup2(fd[0], STDIN_FILENO);
		child_handlers();
		argv = generate_argv_array(program);
		close(tmp_in);
		close(fd[1]);
		execve(path, argv, ms_env);
		close(fd[0]);
	}
	ignore_signals();
	waitpid(id, NULL, 0);
	handle_signals();
	close(fd[0]);
	close(fd[1]);
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


int	is_builtin(char *name)
{
	if (!ft_strncmp(name, "cd", 3))
		return (1);
	else if (!ft_strncmp(name, "echo", 5))
		return (1);
	else if (!ft_strncmp(name, "env", 4))
		return (1);
	else if (!ft_strncmp(name, "export", 7))
		return (1);
	else if (!ft_strncmp(name, "pwd", 4))
		return (1);
	else if (!ft_strncmp(name, "unset", 6))
		return (1);
	return (0);
}

int	execute_builtin(char *name, t_program *program, char **ms_env)
{
	if (!ft_strncmp(name, "cd", 3))
		return (cd(program, ms_env));
	else if (!ft_strncmp(name, "echo", 5))
		return (echo(program));
	else if (!ft_strncmp(name, "env", 4))
	{
		env(ms_env); // TODO: Fix this shit later
		return (0);
	}
	else if (!ft_strncmp(name, "export", 7))
		return (export(program, ms_env));
	else if (!ft_strncmp(name, "pwd", 4))
		return (pwd());
	else if (!ft_strncmp(name, "unset", 6))
		return (unset(program, ms_env));
	return (0);
}

int	execute_one_command(t_program *program, char **ms_env)
{
	char	*path;
	char	**argv;
	int		pid;
	int		ret;

	path = NULL;
	path = it_exists(program->name, ms_env);
	if (path == NULL)
		command_not_found(program->name);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			child_handlers();
			argv = generate_argv_array(program);
			execve(path, argv, ms_env);
			return (1);
		}
		ignore_signals();
		waitpid(pid, &ret, 0);
		handle_signals();
		// TODO: Wife cheated stuff and return
		return (0);
	}
}

void	what_to_do(t_program **pg, char **ms_env)
{
	t_program *program;

	program = *pg;
	if (program->type == SUBSHELL)
		execute_subcommand(program);
	else if (program->next_relation == PIPE)
		execute_pipeliner(program);
	else if (program->next_relation == AND || program->next_relation == OR)
		execute_conditionally(program);
	else if (is_builtin(program->name))
		execute_builtin(program->name, program, ms_env);
	else
		execute_one_command(program, ms_env);
}


void	execute(t_program *program_list)
{
	static char	**ms_env;

	if (!ms_env)
	{
		if (initialize_ms_env(&ms_env))
			printf("ERROR\n");
		if (ms_env == NULL)
		{
			// quit_minishell()
		}
	}
	while (program_list != NULL)
	{
		what_to_do(program_list, ms_env);
		program_list = program_list->next;
	}
}

