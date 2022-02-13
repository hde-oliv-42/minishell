/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:52:00 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/13 19:54:14 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include "ft_printf/libftprintf.h"

static int	str_equals(char *str1, char *str2)
{
	if (str1 == str2)
		return (1);
	return (ft_strncmp(str1, str2, ft_strlen(str1) + 1) == 0);
}

static char	*finish_heredoc(t_list *lines)
{
	char	*full_text;
	char	*tmp;

	tmp = lines->content;
	full_text = ft_strjoin(tmp, "\n");
	lines = lines->next;
	while (lines && lines->next)
	{
		tmp = full_text;
		full_text = ft_strjoin(full_text, lines->content);
		free(tmp);
		tmp = full_text;
		full_text = ft_strjoin(full_text, "\n");
		free(tmp);
		lines = lines->next;
	}
	return (full_text);
}

char	*get_heredoc(char *delimiter)
{
	char	*newstr;
	char	*full_text;
	t_list	*lines_list;

	lines_list = NULL;
	full_text = NULL;
	while (1)
	{
		newstr = readline("> ");
		if (newstr == NULL)
		{
			ft_dprintf(2022, "unexpected end-of-file\n");
			ft_lstclear(&lines_list, free);
			return (NULL);
		}
		ft_lstadd_back(&lines_list, ft_lstnew(newstr));
		if (str_equals(delimiter, newstr))
		{
			full_text = finish_heredoc(lines_list);
			ft_lstclear(&lines_list, free);
			break ;
		}
	}
	return (full_text);
}
