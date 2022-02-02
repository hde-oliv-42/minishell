#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#include <process/process.h>
#include <parsing/parsing.h>
#include <tokenizer/tokenizer.h>
#include <execute/execute.h>
#include <prompt/prompt.h>
#include <libft.h>
#include <ft_printf/libftprintf.h>
#include <errno.h>
#include <sys/wait.h>
#include <debug/debug.h>
#include <execute/execute.h>

int	quit_minishell(void)
{
	// TODO: free stuff
	rl_clear_history();
	exit(0);
}

void	handle_interrupt(void);

int	loop_prompt(void)
{
	char	*line;
	char	*prompt;
	t_token	**tokens;
	t_program	*program;

	handle_interrupt();
	while (1)
	{
		prompt = generate_prompt();
		line = readline(prompt);
		free(prompt);
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
		execute(program);
		destroy_pipeline(program);
		destroy_token_array(tokens);
	}
	return (0);
}

int	main(void)
{
	return (loop_prompt());
}
