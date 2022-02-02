/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:56:23 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/01 18:14:24 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "signals.h"
#include <stdio.h>
#include <libft.h>
#include <stdlib.h>
#include <readline/readline.h>

static void	handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_interrupt(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_INTERRUPT;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		printf("error handling signal\n");
	}
}
