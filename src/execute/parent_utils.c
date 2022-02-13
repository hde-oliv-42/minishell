#include "execute.h"

int	check_conditional_error(t_program *last_program, int wstatus)
{
	if (last_program && last_program->next_relation == AND && wstatus != 0)
		return (1);
	else if (last_program && last_program->next_relation == OR && wstatus == 0)
		return (1);
	return (0);
}

void	handle_wait(t_program *program_list, int *wstatus)
{
	t_program	*tmp;
	int			size;
	int			status;
	int			waifu; // TODO: Change this name later

	tmp = program_list;
	size = 0;
	while (tmp)
	{
		if (tmp->next_relation != OR && tmp->next_relation != AND)
			size++;
		tmp = tmp->next;
	}
	while (size)
	{
		wait(&status);
		size--;
		waifu = WIFEXITED(status);
		if (waifu)
			*wstatus = WEXITSTATUS(status);
		else
			*wstatus = 1;
	}
}

void	handle_conditional_wait(int *wstatus)
{
	int	waifu;
	int	status;

	wait(&status);
	waifu = WIFEXITED(status);
	if (waifu)
		*wstatus = WEXITSTATUS(status);
	else
		*wstatus = 1;
}

void	handle_child(t_program *last_program, t_program *program, int wstatus)
{
	int	out_fd;

	out_fd = 0;
	check_if_must_open_stdin(last_program);
	check_if_must_open_stdout(program);
	open_all_output_files(program, &out_fd);
	open_all_input_files(program, out_fd);
	execute_one_command(last_program, program, &wstatus);
}
