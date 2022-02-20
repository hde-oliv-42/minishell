#include "execute.h"
#include "debug/debug.h"
#include "expand/expand.h"
#include "libft.h"
#include "signals/signals.h"
#include "structures.h"
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

void	handle_subshell(t_data *data)
{
	t_data		tmp;
	t_token		**tokens;
	t_program	*programs;

	handle_signals();
	tokens = tokenize(((t_string *)data->program->params->content)->value);
	if (tokens == NULL)
		flush_minishell(data);
	programs = parse(tokens);
	if (programs == NULL)
		flush_minishell(data);
	destroy_token_array(tokens);
	tmp.wstatus = data->wstatus;
	tmp.must_continue = 1;
	tmp.program_list = programs;
	close(data->program->next_pipe[0]);
	execute(&tmp, programs);
	destroy_pipeline(programs);
	destroy_pipeline(data->program_list);
	tmp.program_list = NULL;
	free(data->cwd);
	ft_dfree(g_env);
	exit(*(tmp.wstatus));
}
