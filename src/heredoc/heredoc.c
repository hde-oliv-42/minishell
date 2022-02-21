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
	t_data *data, t_redirection *redirection, int piper[2])
{
	int		should_stop;
	int		size;
	char	*buffer;

	ignore_signals();
	should_stop = wait_child();
	if (!should_stop)
	{
		read(piper[0], &size, 4);
		buffer = malloc(size + 1);
		buffer[size] = '\0';
		read(piper[0], buffer, size);
		redirection->contents = buffer;
	}
	else
	{
		*data->wstatus = should_stop;
		data->must_continue = 0;
	}
	handle_signals();
	return (should_stop);
}

static int	collect_heredoc(t_redirection *redirection, t_data *data)
{
	int		piper[2];
	int		should_stop;

	should_stop = 0;
	if (redirection->type == RD_HERE_DOC)
	{
		pipe(piper);
		if (fork() == 0)
			child_send_heredoc(redirection, piper, data);
		else
			should_stop = parent_receive_heredoc(data, redirection, piper);
		close_pipe(piper, data);
	}
	return (should_stop);
}

void	collect_heredocs(t_program *programs, t_data *data)
{
	t_list			*item;
	int				should_stop;

	should_stop = 0;
	while (!should_stop && programs != NULL)
	{
		item = programs->input_list;
		while (!should_stop && item)
		{
			should_stop = collect_heredoc(item->content, data);
			item = item->next;
		}
		data->must_continue = !should_stop;
		programs->ret = should_stop;
		programs = programs->next;
	}
}
