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

static void	store_oldpwd(t_program *program, char **oldpwd, t_data *data)
{
	t_string	*str;

	if (!program->params)
	{
		str = ft_calloc(1, sizeof(t_string));
		str->value = ft_strjoin("OLDPWD=", *oldpwd);
		ft_lstadd_back(&program->params, ft_lstnew(str));
		export(program, data);
		free(*oldpwd);
		return ;
	}
	free(((t_string *)program->params->content)->value);
	((t_string *)program->params->content)->value = ft_strjoin("OLDPWD=", \
															*oldpwd);
	export(program, data);
	free(*oldpwd);
}

static int	handle_home(t_program *program, char **pwd, t_data *data)
{
	char	*home;

	home = NULL;
	if (get_var(g_env, &home, "HOME=", 5) != -1)
	{
		if (home == NULL)
		{
			ft_dprintf(2, "minishell: cd: HOME not set\n");
			free(*pwd);
			return (1);
		}
		if (!chdir(home))
		{
			store_oldpwd(program, pwd, data);
			free(home);
			return (0);
		}
		free(*pwd);
		free(home);
	}
	return (1);
}

static int	handle_dash(t_program *program, char **pwd, t_data *data)
{
	char	*oldpwd;

	oldpwd = NULL;
	if (get_var(g_env, &oldpwd, "OLDPWD=", 7) != -1)
	{
		if (oldpwd == NULL)
		{
			ft_dprintf(2, "minishell: cd: OLDPWD not set\n");
			free(*pwd);
			return (1);
		}
		printf("%s\n", oldpwd);
		if (!chdir(oldpwd))
		{
			store_oldpwd(program, pwd, data);
			free(oldpwd);
			return (0);
		}
		free(*pwd);
		free(oldpwd);
	}
	if (errno)
		perror("cd");
	errno = 0;
	return (1);
}

int	cd(t_program *program, t_data *data)
{
	char	*dir;
	char	*oldpwd;

	oldpwd = ft_strdup(data->cwd);
	if (ft_lstsize(program->params) > 1)
		ft_dprintf(2, "minishell: cd: too many arguments\n");
	else if (ft_lstsize(program->params) == 0)
		return (handle_home(program, &oldpwd, data));
	else if (!ft_strncmp(((t_string *)program->params->content)->value, "-", 2))
		return (handle_dash(program, &oldpwd, data));
	else
	{
		dir = ((t_string *)program->params->content)->value;
		if (!chdir(dir))
		{
			store_oldpwd(program, &oldpwd, data);
			return (0);
		}
		if (errno)
			perror("cd");
		errno = 0;
	}
	free(oldpwd);
	return (1);
}
