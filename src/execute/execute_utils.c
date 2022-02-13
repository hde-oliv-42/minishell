#include "execute.h"

char	**generate_argv_array(t_program *program)
{
	char	**argv;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(program->params) + 1;
	argv = (char **)ft_calloc(size + 1, sizeof(char *));
	argv[i++] = ft_strdup(program->name);
	while (i < size)
	{
		argv[i++] = ft_strdup(program->params->content);
		program->params = program->params->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	check_pipe_relations(t_program *last_program, t_program *program)
{
	if (last_program)
	{
		if (close(last_program->next_pipe[1]))
		{
			// flush_minishell();
		}
	}
	if (close(program->next_pipe[0]))
	{
		// flush_minishell();
	}
	if (last_program && last_program->next_relation != PIPE)
	{
		if (close(last_program->next_pipe[0]))
		{
			// flush_minishell();
		}
	}
	if (program->next_relation != PIPE)
	{
		if (close(program->next_pipe[1]))
		{
			// flush_minishell();
		}
	}
}
