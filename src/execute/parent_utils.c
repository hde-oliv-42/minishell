/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/14 21:03:24 by psergio-         ###   ########.fr       */
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
	[SIGPIPE] = "Broken pipe",
	[SIGALRM] = "Alarm clock",
	};

	description = descriptions[signum];
	if (description == NULL)
		description = "";
	return (description);
}

int	check_conditional_error(t_data *data)
{
	if (data->last_program && \
		data->last_program->next_relation == AND && *(data->wstatus) != 0)
		return (1);
	else if (data->last_program \
			&& data->last_program->next_relation == OR \
			&& *(data->wstatus) == 0)
		return (1);
	return (0);
}

void	set_status_code(int wait_pid, int status, t_data *data)
{
	t_program	*program;

	program = data->program_list;
	while (program)
	{
		if (program->pid == wait_pid)
		{
			program->ret = status;
			break ;
		}
		program = program->next;
	}
}

static void	handle_child_death(int wait_pid, int status, t_data *data)
{
	char	*description;
	int		signum;

	if (WIFSIGNALED(status))
	{
		signum = WTERMSIG(status);
		description = get_signal_description(WTERMSIG(status));
		ft_printf("%s", description);
		if (signum == SIGINT)
			data->must_continue = 0;
		if (WCOREDUMP(status))
			ft_printf(" (core dumped)\n");
		set_status_code(wait_pid, signum + 128, data);
		// *(data->wstatus) = signum + 128;
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

void	handle_child(t_data *data)
{
	check_if_must_open_stdin(data, 1);
	check_if_must_open_stdout(data, 1);
	open_all_input_files(data);
	open_all_output_files(data);
	execute_one_command(data);
}
