/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/16 12:44:54 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern char	**environ;

int	initialize_ms_env(char ***ms_env)
{
	int	i;

	i = 0;
	while (environ[i])
		i++;
	*ms_env = ft_calloc(sizeof(char *), (i + 1));
	if (ms_env == NULL)
		return (1);
	i = 0;
	while (environ[i])
	{
		(*ms_env)[i] = ft_strdup(environ[i]);
		if ((*ms_env)[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}

char	*search_env(char *key)
{
	int		i;
	char	*equal_sign;
	char	*current_key;

	i = 0;
	while (g_env[i])
	{
		equal_sign = ft_strchr(g_env[i], '=');
		if (equal_sign == NULL)
			return (NULL);
		current_key = ft_substr(g_env[i], 0, equal_sign - g_env[i]);
		if (str_equals(key, current_key))
		{
			free(current_key);
			return (ft_substr(g_env[i], equal_sign - g_env[i] + 1,
					ft_strlen(g_env[i])));
		}
		i++;
	}
	return (NULL);
}
