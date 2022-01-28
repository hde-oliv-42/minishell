#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <wait.h>

size_t	count_pipes(char *line)
{
	int	count;
	int	in_single_quote;
	int	in_double_quote;

	count = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (*line != '\0')
	{
		if (*line == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*line == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*line == '|' && !in_single_quote && !in_double_quote)
			count++;
		line++;
	}
	return (count);
}

char **make_cmd(char *line)
{
	int		commands;
	char	**cmd;

	commands = count_pipes(line) + 1;
	printf("pipes: %d\n", commands - 1);
	cmd = malloc(sizeof(char *) * commands);
	return (cmd);
}

void	spawn(void)
{
	char	*command[3];
	int		result;
	int		status;
	int		id;

	id = fork();
	if (id == 0)
	{
		command[0] = "/bin/ls";
		command[1] = "-la";
		command[2] = NULL;
		result = execve(command[0], command, NULL);
		if (result)
		{
			perror("Error executing process");
			printf("errno: %d\n", errno);
			exit(errno);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			printf("wife xited\n");
			printf("raw status: %d\n", status);
			printf("actual status: %d\n", WEXITSTATUS(status));
			printf("ENOENT number: %d\n", ENOENT);
		}
		else
		{
			printf("wife didn't xited\n");
		}
	}
}
