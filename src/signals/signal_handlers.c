/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:56:23 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/18 19:44:09 by psergio-         ###   ########.fr       */
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
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signum;
}

void	handle_signals(void)
{
	struct sigaction		sa;
	struct sigaction		sa_quit;

	sigemptyset(&sa.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		printf("error handling signal SIGINT\n");
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		printf("error handling signal SIGQUIT\n");
}

void	reset_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		printf("error reseting the signal handler\n");
}

void	reset_child_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		printf("failed to reset the handler for SIGINT\n");
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		printf("failed to reset the handler for SIGQUIT\n");
}
