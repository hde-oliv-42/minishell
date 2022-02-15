/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/06 20:23:59 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	get_home(char **ms_env, char **home)
{
	int	i;

	i = 0;
	while (ms_env[i])
	{
		if (!ft_strncmp(ms_env[i], "HOME=", 5))
		{
			*home = ft_substr(ms_env[i], 5, ft_strlen(ms_env[i]) - 5);
			if (*home == NULL)
				return (-1);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	handle_home(char **home, char **ms_env)
{
	if (get_home(ms_env, home) != -1)
	{
		if (*home == NULL)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
		if (chdir(*home))
		{
			free(*home);
			return (0);
		}
		free(*home);
	}
	return (1);
}

int	cd(t_program *program, char **ms_env)
{
	int		i;
	char	*home;

	i = ft_lstsize(program->params);
	home = NULL;
	if (i > 1)
		printf("minishell: cd: too many arguments\n");
	else if (i == 0)
		return (handle_home(&home, ms_env));
	else
	{
		if (!chdir(program->params->content))
			return (0);
	}
	return (1);
}
