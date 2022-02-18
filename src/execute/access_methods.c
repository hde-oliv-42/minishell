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

int	is_writable(char *path)
{
	if (!access(path, W_OK))
		return (1);
	return (0);
}

int	is_readable(char *path)
{
	if (!access(path, R_OK))
		return (1);
	return (0);
}

int	is_executable(char *path)
{
	if (!access(path, X_OK))
		return (1);
	return (0);
}

char	*find_path(char *name, char **ms_env)
{
	char	*path_string;
	char	**path_array;

	path_string = NULL;
	fetch_path_string(ms_env, &path_string);
	if (path_string == NULL)
		return (NULL);
	if (create_path_array(path_string, &path_array))
		return (NULL);
	return (loop_path_array(name, path_array));
}
