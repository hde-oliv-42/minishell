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

void	print_pipeline(t_program *program)
{
	t_list	*params;
	t_list	*infile;
	t_list	*outfile;
	t_redirection *redirection;

	while (program)
	{
		printf("=== program ===\n");
		printf("  name: %s\n", program->name);
		printf("  params: [ ");
		params = program->params;
		while (params)
		{
			printf("%s, ", (char *)params->content);
			params = params->next;
		}
		printf("NULL ]\n");
		printf("  infiles: [ ");
		infile = program->input_list;
		while (infile)
		{
			redirection = infile->content;
			printf("<");
			if (redirection->type == HERE_DOC)
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
			if (redirection->type == OUTFILE_APPEND)
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
			else
				type = "|";
			printf("  next: %s %s\n", type, program->next->name);
		}
		program = program->next;
	}
}

int	quit_minishell(void)
{
	// TODO: free stuff
	return (0);
}

// TODO: validate the command string
int	is_valid(char *line)
{
	(void)line;
	// printf("minishell: parse error\n");
	return (1);
}

char	*generate_prompt(void)
{
	return ("minishell$ ");
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
		printf("[%s] %s\n", type, tokens[i]->value);
		if (tokens[i]->type == TK_OPEN_PARENTHESIS)
			open_parenthesis++;
		else if (tokens[i]->type == TK_CLOSE_PARENTHESIS)
			open_parenthesis--;
		i++;
	}
}

int	main(void)
{
	char	*line;
	char	*prompt;
	t_token	**tokens;

	while (1)
	{
		prompt = generate_prompt();
		line = readline(prompt);
		if (line == NULL)
			return (quit_minishell());
		add_history(line);
		tokens = tokenize(line);
		if (tokens == NULL)
		{
			free(line);
			continue ;
		}
		print_tokens(tokens);
		destroy_token_array(tokens);
		free(line);
	}
}
