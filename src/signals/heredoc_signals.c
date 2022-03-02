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
#include "libft.h"
#include "parsing/parsing.h"
#include "signals.h"
#include <readline/readline.h>

int	heredoc_handler(int signum, void *data_ptr, void *list_ptr)
{
	static t_data	*data;
	static t_list	**string_list;

	if (signum == -1)
	{
		data = data_ptr;
		string_list = list_ptr;
	}
	else
	{
		ft_putchar_fd('\n', 1);
		ft_lstclear(string_list, free);
		free(data->cwd);
		destroy_pipeline(data->program_list);
		rl_clear_history();
		ft_dfree(g_env);
		exit(130);
	}
	return (0);
}

void	set_heredoc_signals(t_data *data, t_list **string_list)
{
	void	*handler_pointer;

	handler_pointer = &heredoc_handler;
	heredoc_handler(-1, data, string_list);
	if (signal(SIGINT, (void (*)(int))handler_pointer) == SIG_ERR)
	{
		ft_dprintf(2, "failed to set the heredoc handler for SIGINT\n");
		perror("heredoc_signals");
	}
}
