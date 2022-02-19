/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_subprocess.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:38:19 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/19 15:09:59 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <minishell.h>
#include <readline/readline.h>
#include "heredoc.h"

int	wait_child(void)
{
	int	result;
	int	wstatus;

	result = wait(&wstatus);
	while (result == -1 && errno == EINTR)
	{
		errno = 0;
		result = wait(&wstatus);
	}
	if (errno == ECHILD)
		errno = 0;
	if (result == -1 && errno)
		perror("heredoc");
	if (WIFEXITED(wstatus))
		if (WEXITSTATUS(wstatus) == 0)
			return (1);
	return (0);
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
			ft_dprintf(2, "unexpected end-of-file, expeceted '%s'\n",
				delimiter);
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

void	child_send_heredoc(
	t_redirection *redirection, int piper[2], t_data *data)
{
	int	size;

	set_heredoc_signals();
	redirection->contents = get_heredoc(redirection->file_name);
	size = ft_strlen(redirection->contents);
	write(piper[1], &size, 4);
	write(piper[1], redirection->contents, size);
	close_pipe(piper, data);
	quit_minishell(data);
}
