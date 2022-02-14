#include "execute.h"

void	command_not_found(char *program_name)
{
	ft_dprintf(2, "minishell: %s: command not found\n", program_name);
}

void	flush_minishell(t_data *data)
{
	(void)data;
	exit(errno);
}

void	close_pipe(int fd[2], t_data *data)
{
	if (close(fd[0]))
		flush_minishell(data);
	if (close(fd[1]))
		flush_minishell(data);
}

void	free_minishell(t_data *data)
{
	(void)data;
}
