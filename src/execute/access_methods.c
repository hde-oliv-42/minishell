/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/29 20:23:59 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"

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

char	*find_path(char *name, char **ms_env)
{
	char	*path_string;
	char	**path_array;
	char	*tmp;
	char	*tmp2;
	int		i;

	path_string = NULL;
	fetch_path_string(ms_env, &path_string);
	if (path_string == NULL)
		return (NULL);
	if (create_path_array(path_string, &path_array))
		return (NULL);
	i = 0;
	while (path_array[i])
	{
		tmp = ft_strjoin(path_array[i++], "/");
		tmp2 = ft_strjoin(tmp, name);
		free(tmp);
		if (!access(tmp2, F_OK))
		{
			free_path_array(path_array);
			return (tmp2);
		}
		free(tmp2);
	}
	free_path_array(path_array);
	return (NULL);
}
