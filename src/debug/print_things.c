#include "debug.h"
#include "parsing/parsing.h"

void	print_pipeline(t_program *program)
{
	t_list	*params;
	t_list	*infile;
	t_list	*outfile;
	t_redirection *redirection;

	while (program)
	{
		printf("=== program ===\n");
		printf("  name: %s\n", ((t_string *)program->name)->value);
		printf("  params: [ ");
		params = program->params;
		while (params)
		{
			printf("%s, ", ((t_string *)params->content)->value);
			params = params->next;
		}
		printf("NULL ]\n");
		printf("  infiles: [ ");
		infile = program->input_list;
		while (infile)
		{
			redirection = infile->content;
			printf("<");
			if (redirection->type == RD_HERE_DOC)
				printf("<");
			printf(" %s, ", redirection->file_name);
			infile = infile->next;
		}
		printf("NULL ]\n");
		printf("  output: [ ");
		outfile = program->output_list;
		while (outfile)
		{
			redirection = outfile->content;
			printf(">");
			if (redirection->type == RD_OUTFILE_APPEND)
				printf(">");
			printf(" %s, ", redirection->file_name);
			outfile = outfile->next;
		}
		printf("NULL ]\n");
		if (program->next)
		{
			char *type;
			if (program->next_relation == OR)
				type = "||";
			else if (program->next_relation == AND)
				type = "&&";
			else if (program->next_relation == PIPE)
				type = "|";
			else
				type = "!!!!!!";
			printf("  next: %s %s\n", type, (char *)program->next->name);
		}
		program = program->next;
	}
}

// TODO: validate the command string
int	is_valid(char *line)
{
	(void)line;
	// printf("minishell: parse error\n");
	return (1);
}


char	**generate_argv(t_program *program)
{
	int		i;
	int		size;
	char	**array;
	t_list	*params;

	params = program->params;
	size = ft_lstsize(program->params);
	array = ft_calloc(size + 2, sizeof(char **));
	if (array == NULL)
		exit(2);
	array[0] = program->name;
	i = 1;
	while (params)
	{
		array[i] = params->content;
		params = params->next;
		i++;
	}
	return (array);
}

void	print_array(char **array)
{
	while (*array)
	{
		printf(" %s\n", *array);
		array++;
	}
}

void	execute_pipeline(t_program *pipeline)
{
	char	**argv;
	int		pid;

	// print_pipeline(pipeline);
	while (pipeline)
	{
		// print_array(argv);
		pid = fork();
		if (pid == 0)
		{
			argv = generate_argv(pipeline);
			execve(pipeline->name, argv, NULL);
			if (errno == ENOENT)
				printf("minishell: command not found\n");
			else
				perror("minishell");
			exit(errno);
		}
		else
		{
			wait(NULL);
		}
		pipeline = pipeline->next;
	}
}

void	print_tokens(t_token **tokens)
{
	int		i;
	int		open_parenthesis = 0;
	char	*type;
	char	*token_str[TK_MAX] = {
		[TK_WORD] = "WORD",
		[TK_OPEN_PARENTHESIS] = "OPEN PARENTHESIS",
		[TK_CLOSE_PARENTHESIS] = "CLOSE PARENTHESIS",
		[TK_REDIRECT_IN_FILE] = "REDIRECT IN",
		[TK_REDIRECT_IN_HEREDOC] = "HEREDOC",
		[TK_REDIRECT_OUT_APPEND] = "REDIRECT APPEND",
		[TK_REDIRECT_OUT_TRUNC] = "REDIRECT TRUNCATE",
		[TK_AND] = "AND",
		[TK_OR] = "OR",
		[TK_PIPE] = "PIPE",
	};

	i = 0;
	while (tokens[i])
	{
		type = token_str[tokens[i]->type];
		int indent = 0;
		while (indent++ < open_parenthesis)
			printf("   ");
		printf("[%s] %s ", type, tokens[i]->value);
		if (tokens[i]->should_expand)
			printf("*");
		printf("\n");
		if (tokens[i]->type == TK_OPEN_PARENTHESIS)
			open_parenthesis++;
		else if (tokens[i]->type == TK_CLOSE_PARENTHESIS)
			open_parenthesis--;
		i++;
	}
}
