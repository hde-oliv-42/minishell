#include "execute.h"

void	command_not_found(char *program_name)
{
	ft_dprintf(2, "minishell: %s: command not found\n", program_name);
}

void	flush_minishell(void)
{
	// Cancel everything and print prompt
}

void	close_pipe(int fd[2])
{
	if (close(fd[0]))
		quit_minishell();
	if (close(fd[1]))
		quit_minishell();
}
