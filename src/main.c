#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#include <process/process.h>
#include <parsing/parsing.h>
#include <tokenizer/tokenizer.h>
#include <libft.h>
#include <errno.h>
#include <sys/wait.h>
#include <debug/debug.h>

char	*generate_prompt(void)
{
	return ("minishell$ ");
}

int	quit_minishell(void)
{
	// TODO: free stuff
	return (0);
}

int	main(void)
{
	char	*line;
	char	*prompt;
	t_token	**tokens;
	t_program	*program;

	while (1)
	{
		prompt = generate_prompt();
		line = readline(prompt);
		if (line == NULL)
			return (quit_minishell());
		add_history(line);
		tokens = tokenize(line);
		free(line);
		if (tokens == NULL)
			continue ;
		program = parse(tokens);
		if (program == NULL)
			continue ;
		print_pipeline(program);
		destroy_pipeline(program);
		destroy_token_array(tokens);
	}
	rl_clear_history();
}
