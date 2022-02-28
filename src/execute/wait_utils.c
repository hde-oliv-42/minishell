/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:49 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug/debug.h"
#include "execute.h"
#include "structures.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

static char	*get_signal_description(int signum)
{
	char		*description;
	static char	*descriptions[128] = {
	[SIGILL] = "Illegal instruction",
	[SIGABRT] = "Abort",
	[SIGSEGV] = "Segmentation fault",
	[SIGTERM] = "Terminated",
	[SIGHUP] = "Hangup",
	[SIGQUIT] = "Quit",
	[SIGKILL] = "Killed",
	[SIGALRM] = "Alarm clock",
	};

	description = descriptions[signum];
	return (description);
}

static void	handle_child_death(int wait_pid, int status, t_data *data)
{
	char	*description;
	int		signum;

	if (WIFSIGNALED(status))
	{
		signum = WTERMSIG(status);
		description = get_signal_description(WTERMSIG(status));
		if (signum == SIGINT)
			data->must_continue = 0;
		if (description)
			ft_printf("%s", description);
		if (WCOREDUMP(status))
			ft_printf(" (core dumped)");
		if (description != NULL)
			ft_printf("\n");
		set_status_code(wait_pid, signum + 128, data);
	}
	else
		set_status_code(wait_pid, 0, data);
}

void	handle_wait(t_data *data)
{
	int		size;
	int		status;
	int		wait_result;

	size = data->program_count;
	while (size)
	{
		wait_result = wait(&status);
		if (wait_result == -1 && errno == EINTR)
			continue ;
		size--;
		if (WIFEXITED(status))
			set_status_code(wait_result, WEXITSTATUS(status), data);
		else
			handle_child_death(wait_result, status, data);
	}
}

void	handle_conditional_wait(t_data *data)
{
	int	status;
	int	wait_result;

	while (1)
	{
		wait_result = wait(&status);
		if (wait_result == -1 && errno == EINTR)
		{
			errno = 0;
			continue ;
		}
		if (WIFEXITED(status))
			set_status_code(wait_result, WEXITSTATUS(status), data);
		else
			handle_child_death(wait_result, status, data);
		break ;
	}
}
