/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:57:24 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/19 15:45:08 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"
#include "parsing/parsing.h"
#include "signals.h"

int	heredoc_handler(int signum, void *data_ptr)
{
	static t_data	*data;

	if (signum == -1)
		data = data_ptr;
	else
	{
		free(data->cwd);
		destroy_pipeline(data->program_list);
		exit(130);
	}
	return (0);
}

void	set_heredoc_signals(t_data *data)
{
	void	*handler_pointer;

	handler_pointer = &heredoc_handler;
	heredoc_handler(-1, data);
	if (signal(SIGINT, (void (*)(int))handler_pointer) == SIG_ERR)
	{
		printf("failed to set the heredoc handler for SIGINT\n");
		perror("heredoc_signals");
	}
}
