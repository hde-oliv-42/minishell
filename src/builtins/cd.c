/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:15 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "debug/debug.h"
#include "libft.h"
#include "parsing/parsing.h"
#include "structures.h"
#include <stdio.h>

static int	get_var(char **ms_env, char **ret, char *var, int var_siz)
{
	int	i;

	i = 0;
	while (ms_env[i])
	{
		if (!ft_strncmp(ms_env[i], var, var_siz))
		{
			*ret = ft_substr(ms_env[i], var_siz, \
							ft_strlen(ms_env[i]) - var_siz);
			if (*ret == NULL)
				return (-1);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	store_oldpwd(t_program *program, char **oldpwd, char ***ms_env)
{
	t_string	*str;

	if (!program->params)
	{
		str = ft_calloc(1, sizeof(t_string));
		str->value = ft_strjoin("OLDPWD=", *oldpwd);
		ft_lstadd_back(&program->params, ft_lstnew(str));
		export(program, ms_env);
		free(*oldpwd);
		return ;
	}
	free(((t_string *)program->params->content)->value);
	((t_string *)program->params->content)->value = ft_strjoin("OLDPWD=", \
															*oldpwd);
	export(program, ms_env);
	free(*oldpwd);
}

static int	handle_home(t_program *program, char **pwd, char ***ms_env)
{
	char	*home;

	home = NULL;
	if (get_var(*ms_env, &home, "HOME=", 5) != -1)
	{
		if (home == NULL)
		{
			ft_dprintf(2, "minishell: cd: HOME not set\n");
			return (1);
		}
		if (!chdir(home))
		{
			store_oldpwd(program, pwd, ms_env);
			free(home);
			return (0);
		}
		free(*pwd);
		free(home);
	}
	return (1);
}

static int	handle_dash(t_program *program, char **pwd, char ***ms_env)
{
	char	*oldpwd;

	oldpwd = NULL;
	if (get_var(*ms_env, &oldpwd, "OLDPWD=", 7) != -1)
	{
		if (oldpwd == NULL)
		{
			ft_dprintf(2, "minishell: cd: OLDPWD not set\n");
			return (1);
		}
		printf("%s\n", oldpwd);
		if (!chdir(oldpwd))
		{
			store_oldpwd(program, pwd, ms_env);
			free(oldpwd);
			return (0);
		}
		free(*pwd);
		free(oldpwd);
	}
	return (1);
}

int	cd(t_program *program, char ***ms_env)
{
	int		i;
	char	*dir;
	char	*oldpwd;

	i = ft_lstsize(program->params);
	oldpwd = getcwd(NULL, 0);
	if (i > 1)
		ft_dprintf(2, "minishell: cd: too many arguments\n");
	else if (i == 0)
		return (handle_home(program, &oldpwd, ms_env));
	else if (!ft_strncmp(((t_string *)program->params->content)->value, "-", 2))
		return (handle_dash(program, &oldpwd, ms_env));
	else
	{
		dir = ((t_string *)program->params->content)->value;
		if (!chdir(dir))
		{
			store_oldpwd(program, &oldpwd, ms_env);
			return (0);
		}
	}
	free(oldpwd);
	return (1);
}
