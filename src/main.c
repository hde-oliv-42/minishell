#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

#include <process/process.h>
#include <parsing/parsing.h>
#include <libft.h>

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

void	execute_pipeline(t_program *pipeline)
{
	while (pipeline)
	{
		// TODO: connect and execute the programs in the pipeline
		pipeline = pipeline->next;
	}
}

int	main(void)
{
	char		*line;
	t_program	*pipeline;
	int			cursor;
	char		*prompt;

	while (1)
	{
		prompt = generate_prompt();
		line = readline(prompt);
		if (line == NULL)
			return (quit_minishell());
		if (!is_valid(line))
			continue ;
		cursor = 0;
		pipeline = parse_pipeline(line, &cursor);
		if (pipeline == NULL)
			continue ;
		print_pipeline(pipeline);
		destroy_pipeline(pipeline);
		free(line);
	}
}
