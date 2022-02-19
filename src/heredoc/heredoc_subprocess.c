/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_subprocess.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:38:19 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/19 14:59:19 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <minishell.h>
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
