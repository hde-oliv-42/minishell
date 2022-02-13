/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 08:57:31 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/13 16:17:38 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug/debug.h"
#include "expand.h"
#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <libft.h>

int	compare(char *str1, char *str2)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str1);
	while (i < size && str2[i] != '\0')
	{
		if (ft_tolower(str1[i]) > ft_tolower(str2[i]))
			return (1);
		else if (ft_tolower(str1[i]) < ft_tolower(str2[i]))
			return (-1);
		i++;
	}
	if (i < size)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	else
		return (0);
}

void	sort_directories(char **file_names)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (file_names[i])
	{
		j = i + 1;
		while (file_names[j])
		{
			if (compare(file_names[i], file_names[j]) > 0)
			{
				tmp = file_names[i];
				file_names[i] = file_names[j];
				file_names[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static char	**string_list_to_array(t_list *list)
{
	int		i;
	int		size;
	char	**arr;

	size = ft_lstsize(list);
	arr = malloc(sizeof(char *) * (size + 1));
	arr[size] = NULL;
	i = 0;
	while (list)
	{
		arr[i++] = list->content;
		list = list->next;
	}
	return (arr);
}

static t_list	*array_to_list(char **file_names_array)
{
	t_list	*list;
	char	**array_pointer;

	list = NULL;
	array_pointer = file_names_array;
	while (*file_names_array)
	{
		ft_lstadd_back(&list, ft_lstnew(*file_names_array));
		file_names_array++;
	}
	free(array_pointer);
	return (list);
}

t_list	*expand_asterisk(void)
{
	DIR				*dir;
	struct dirent	*dir_data;
	t_list			*file_names;
	char			**file_names_array;

	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	dir_data = readdir(dir);
	file_names = NULL;
	while (dir_data != NULL && !errno)
	{
		if (dir_data->d_name[0] != '.')
			ft_lstadd_back(&file_names, ft_lstnew(ft_strdup(dir_data->d_name)));
		dir_data = readdir(dir);
	}
	if (errno)
		perror("readdir");
	file_names_array = string_list_to_array(file_names);
	sort_directories(file_names_array);
	closedir(dir);
	ft_lstclear(&file_names, do_nothing);
	return (array_to_list(file_names_array));
}
