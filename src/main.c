#include "expand/expand.h"
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
#include <execute/execute.h>
#include <signals/signals.h>
#include <debug/debug.h>

int	quit_minishell(void)
{
	// TODO: free stuff
	rl_clear_history();
	exit(0);
}

int	loop_prompt(void)
{
	char	*line;
	char	*prompt;
	t_token	**tokens;
	t_program	*program;

	handle_signals();
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
	/* char *strings[] = { */
	/* 	"minishell", */
	/* 	"mi'ni'sh'ell'", */
	/* 	"mi\"ni\"sh'ell'", */
	/* 	"mi\"ni'shell'\"", */
	/* 	"mi'ni''sh''ell'", */
	/* 	"mi\"\"ni\"sh\"\"ell\"", */
	/* 	"'mi\"\"ni\"sh\"\"ell\"'", */
	/* 	"'mi\"\"ni\"sh'\"\"ell\"\"", */
	/* 	"\"mini shell\"", */
	/* 	"$USER", */
	/* 	"'$USER'", */
	/* 	"\"$USER\"", */
	/* 	"echo\"$USER\"", */
	/* 	"echo$USER", */
	/* 	"echo$USER$USER", */
	/* 	"echo$US$ER$USER", */
	/* 	"\"$USER é legal\"", */
	/* 	"'$USER é legal'", */
	/* 	"$$USER é legal", */
	/* 	"$=USER é legal", */
	/* 	"$@USER é legal", */
	/* 	"$(USER é legal", */
	/* 	"$)USER é legal", */
	/* 	"$*USER é legal", */
	/* 	"dsjak lfads jfkdl sjf (ajsdkfl jdskf jasdkl)", */
	/* 	"massa$", */
	/* 	"\"daora$\"", */
	/* 	"\"daora$\"massa", */
	/* 	NULL}; */
	/* int i = 0; */

	/* while (strings[i]) */
	/* { */
	/* 	char *expanded = expand_word(strings[i]); */
	/* 	printf("\nactual:   %s\n", strings[i]); */
	/* 	printf("expanded: %s\n", expanded); */
	/* 	free(expanded); */
	/* 	i++; */
	/* } */
	return (loop_prompt());
}
