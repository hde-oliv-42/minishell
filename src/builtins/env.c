/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:53:10 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:18 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parsing/parsing.h"
#include "structures.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static int	quit_env(t_data *data)
{
	free(data->cwd);
	destroy_pipeline(data->program_list);
	rl_clear_history();
	ft_dfree(g_env);
	exit(0);
}

static void	print_env(void)
{
	int	i;

	i = 0;
	while (g_env[i])
		printf("%s\n", g_env[i++]);
}

int	env(t_program *program, t_data *data)
{
	int	pid;

	if (program->next_relation == PIPE)
	{
		pid = fork();
		if (pid == 0)
		{
			close(program->next_pipe[0]);
			print_env();
			quit_env(data);
		}
		program->pid = pid;
		data->program_count++;
	}
	else
		print_env();
	return (0);
}
