/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:52:00 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/19 15:09:59 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "ft_printf/libftprintf.h"
#include "heredoc.h"
#include <minishell.h>
#include "parsing/parsing.h"
#include "signals/signals.h"

static int	parent_receive_heredoc(
	t_redirection *redirection, int piper[2])
{
	int		should_continue;
	int		size;
	char	*buffer;

	ignore_signals();
	should_continue = wait_child();
	if (should_continue)
	{
		read(piper[0], &size, 4);
		buffer = malloc(size + 1);
		buffer[size] = '\0';
		read(piper[0], buffer, size);
		redirection->contents = buffer;
	}
	handle_signals();
	return (should_continue);
}

static int	collect_heredoc(t_redirection *redirection, t_data *data)
{
	int		piper[2];
	int		should_continue;

	should_continue = 0;
	if (redirection->type == RD_HERE_DOC)
	{
		pipe(piper);
		if (fork() == 0)
			child_send_heredoc(redirection, piper, data);
		else
			should_continue = parent_receive_heredoc(redirection, piper);
		close_pipe(piper, data);
	}
	return (should_continue);
}

void	collect_heredocs(t_program *programs, t_data *data)
{
	t_list			*item;
	int				should_continue;

	should_continue = 1;
	while (should_continue && programs != NULL)
	{
		item = programs->input_list;
		while (should_continue && item)
		{
			should_continue = collect_heredoc(item->content, data);
			item = item->next;
		}
		data->must_continue = should_continue;
		programs = programs->next;
	}
}
