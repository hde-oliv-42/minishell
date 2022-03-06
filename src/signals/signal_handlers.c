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
#include "ft_printf/libftprintf.h"
#include "prompt/prompt.h"
#include "structures.h"

void	sigint_handler(int signum, t_data *out_data)
{
	static t_data	*data;
	char			*prompt;

	if (signum == -1)
	{
		data = out_data;
		return ;
	}
	else
		data->wstatus = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	prompt = generate_prompt(data);
	rl_set_prompt(prompt);
	rl_redisplay();
}

void	handle_signals(void)
{
	struct sigaction		sa;
	struct sigaction		sa_quit;
	void					*handler;

	sigemptyset(&sa.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa_quit.sa_mask, SIGQUIT);
	sa.sa_flags = SA_RESTART;
	handler = sigint_handler;
	sa.sa_handler = handler;
	sa_quit.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_dprintf(2, "error handling signal SIGINT\n");
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		ft_dprintf(2, "error handling signal SIGQUIT\n");
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
		ft_dprintf(2, "error reseting the signal handler\n");
}

void	reset_child_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_INTERRUPT;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		ft_dprintf(2, "failed to reset the handler for SIGINT\n");
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		ft_dprintf(2, "failed to reset the handler for SIGQUIT\n");
}
