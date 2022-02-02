/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/29 20:23:59 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern char **environ;

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
