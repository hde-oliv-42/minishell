/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:35 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "ft_printf/libftprintf.h"

int	create_path_array(char *path_string, char ***path_array)
{
	char	*str;

	str = ft_substr(path_string, 5, ft_strlen(path_string) - 5);
	*path_array = ft_split(str, ':');
	free(str);
	if (*path_array == NULL)
		return (1);
	return (0);
}

void	free_path_array(char **path_array)
{
	int	i;

	i = 0;
	while (path_array[i])
	{
		free(path_array[i]);
		i++;
	}
	free(path_array);
}

void	fetch_path_string(char **ms_env, char **path_string)
{
	int		i;

	i = 0;
	while (ms_env[i])
	{
		if (!ft_strncmp(ms_env[i], "PATH=", 5))
		{
			*path_string = ms_env[i];
			break ;
		}
		i++;
	}
}

int	is_relative(char *name)
{
	if (name[0] == '.' || (ft_strchr(&(name[1]), '/') && name[0] != '/' ))
	{
		if (!access(name, F_OK))
			return (1);
		return (-1);
	}
	else if (name[0] == '/')
	{
		if (!access(name, F_OK))
			return (1);
		return (-1);
	}
	return (0);
}

char	*loop_path_array(char *name, char **path_array)
{
	int		i;
	char	*tmp2;

	i = is_relative(name);
	if (i == 1)
		return (ft_strdup(name));
	else if (i == -1)
		return (NULL);
	i = 0;
	while (path_array[i])
	{
		ft_asprintf(&tmp2, "%s/%s", path_array[i++], name);
		if (!access(tmp2, F_OK))
			return (tmp2);
		free(tmp2);
	}
	return (NULL);
}
