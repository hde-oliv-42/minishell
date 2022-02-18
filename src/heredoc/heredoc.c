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
#include "heredoc.h"
#include "parsing/parsing.h"

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
			ft_dprintf(2, "unexpected end-of-file, expeceted '%s'\n",
				delimiter);
			ft_lstclear(&lines_list, free);
			return (NULL);
		}
		ft_lstadd_back(&lines_list, ft_lstnew(newstr));
		printf("you typed: %s\n", newstr);
		if (str_equals(delimiter, newstr))
		{
			full_text = finish_heredoc(lines_list);
			ft_lstclear(&lines_list, free);
			break ;
		}
	}
	return (full_text);
}

void	collect_heredocs(t_program *programs)
{
	char			*heredoc;
	char			*delimiter;
	t_list			*item;
	t_redirection	*redirection;

	while (programs)
	{
		item = programs->input_list;
		while (item)
		{
			redirection = item->content;
			if (redirection->type == RD_HERE_DOC)
			{
				delimiter = redirection->file_name;
				heredoc = get_heredoc(delimiter);
				redirection->contents = heredoc;
			}
			item = item->next;
		}
		programs = programs->next;
	}
}
