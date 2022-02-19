#include "expand/expand.h"
#include "heredoc/heredoc.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

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

void	destroy_data(t_data *data)
{
	// destroy_pipeline(data->program_list);
	data->cwd = NULL;
}

int	quit_minishell(t_data *data)
{
	// TODO: free stuff
	free(data->cwd);
	rl_clear_history();
	ft_dfree(g_env);
	ft_printf("exit\n");
	exit(0);
}

t_program	*get_program_pipeline(t_data *data)
{
	char	*line;
	char	*prompt;
	t_token	**tokens;
	t_program	*programs;

	prompt = generate_prompt(data);
	line = readline(prompt);
	free(prompt);
	if (line == NULL)
		quit_minishell(data);
	if (ft_strlen(line) == 0)
		return (NULL);
	add_history(line);
	tokens = tokenize(line);
	free(line);
	if (tokens == NULL)
		return (NULL);
	programs = parse(tokens);
	if (programs == NULL)
		return (NULL);
	destroy_token_array(tokens);
	return (programs);
}

int	loop_prompt(t_data *data)
{
	t_program	*programs;

	handle_signals();
	while (1)
	{
		programs = get_program_pipeline(data);
		// print_pipeline(programs);
		if (programs == NULL)
			continue ;
		data->must_continue = 1;
		collect_heredocs(programs, data);
		execute(data, programs);
		destroy_pipeline(programs);
	}
	return (0);
}

int	main(void)
{
	t_data	data;
	int		wstatus;

	ft_bzero(&data, sizeof(t_data));
	wstatus = 0;
	initialize_ms_env(&g_env);
	data.wstatus = &wstatus;
	return (loop_prompt(&data));
}
