/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:27:19 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:09 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ms_env_size(char **ms_env)
{
	int	i;

	i = 0;
	while ((ms_env)[i++])
	{
	}
	return (i);
}

int	duplicate_env(char **ms_env, char ***tmp)
{
	int	i;

	i = ms_env_size(ms_env);
	*tmp = (char **) ft_calloc(i + 1, sizeof(char *));
	if (*tmp == NULL)
		return (1);
	i = 0;
	while (ms_env[i])
	{
		(*tmp)[i] = ft_strdup(ms_env[i]);
		if ((*tmp)[i] == NULL)
		{
			ft_dfree(*tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

void	export_error(char *str, char *err)
{
	ft_dprintf(2, err, str);
}

int	swap_env(char ***ms_env, char **new_env, int i)
{
	if (i != 0)
		return (1);
	else
	{
		ft_dfree(*ms_env);
		*ms_env = new_env;
		return (0);
	}
	return (1);
}
