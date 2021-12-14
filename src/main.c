#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

int	main(void)
{
	char	*line;

	line = readline("minishell > ");
	printf("you typed: [ %s ]\n", line);
	free(line);
}
