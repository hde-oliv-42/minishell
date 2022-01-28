/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:38:43 by psergio-          #+#    #+#             */
/*   Updated: 2022/01/25 13:22:56 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing/parsing.h"
#include "tokenizer/tokenizer.h"
#include <stdlib.h>
#include <unistd.h>

static int	is_end_of_program(t_token *token)
{
	return (
		token == NULL
		|| token->type == TK_PIPE
		|| token->type == TK_AND
		|| token->type == TK_OR
	);
}

static t_redirection	*parse_redirection(t_token **tokens, int *cursor)
{
	t_redirection		*redirection;
	t_redirection_type	type[TK_MAX];

	redirection = malloc(sizeof(t_redirection));
	if (redirection == NULL)
		return (NULL);
	type[TK_REDIRECT_IN_FILE] = RD_INFILE;
	type[TK_REDIRECT_IN_HEREDOC] = RD_HERE_DOC;
	type[TK_REDIRECT_OUT_APPEND] = RD_OUTFILE_APPEND;
	type[TK_REDIRECT_OUT_TRUNC] = RD_OUTFILE_TRUNC;
	redirection->type = type[tokens[*cursor]->type];
	redirection->file_name = tokens[*cursor + 1]->value;
	(*cursor) = *cursor + 2;
	return (redirection);
}

static int	add_redirection(t_program *program, t_token **tokens, int *cursor)
{
	t_redirection	*redirection;
	t_list			*new_element;
	t_list			**list;

	if (tokens[*cursor]->type == TK_REDIRECT_IN_FILE
		|| tokens[*cursor]->type == TK_REDIRECT_IN_HEREDOC)
		list = &program->input_list;
	else
		list = &program->output_list;
	redirection = parse_redirection(tokens, cursor);
	if (redirection == NULL)
		return (0);
	new_element = ft_lstnew(redirection);
	if (new_element == NULL)
		return (free(redirection), 0);
	ft_lstadd_back(list, new_element);
	return (1);
}

static int	handle_word(t_program *program, t_token **tokens, int *cursor)
{
	char	*word;
	t_list	*new_param;

	word = tokens[*cursor]->value;
	if (program->name == NULL)
		program->name = word;
	else
	{
		new_param = ft_lstnew(word);
		if (new_param == NULL)
			return (0);
		ft_lstadd_back(&program->params, ft_lstnew(word));
	}
	(*cursor)++;
	return (1);
}

t_program	*parse_program(t_token **tokens, int *cursor)
{
	t_program	*program;
	int			success;

	program = ft_calloc(sizeof(t_program), 1);
	if (program == NULL)
		return (NULL);
	while (!is_end_of_program(tokens[*cursor]))
	{
		success = 0;
		if (is_redirection_tk(tokens[*cursor]->type))
			success = add_redirection(program, tokens, cursor);
		else if (is_parenthesis_tk(tokens[*cursor]->type))
			success = make_subshell(program, tokens, cursor);
		else
			success = handle_word(program, tokens, cursor);
		if (!success)
		{
			destroy_program(program);
			return (NULL);
		}
	}
	return (program);
}

static void	set_next_relation(t_program *program, t_token *token)
{
	if (token->type == TK_PIPE)
		program->next_relation = PIPE;
	else if (token->type == TK_AND)
		program->next_relation = AND;
	else if (token->type == TK_OR)
		program->next_relation = OR;
}

t_program	*parse(t_token **tokens)
{
	int			tk_cursor;
	t_program	*program;
	t_program	*tmp;

	tk_cursor = 0;
	program = parse_program(tokens, &tk_cursor);
	if (program == NULL)
		return (NULL);
	tmp = program;
	while (tokens[tk_cursor] && is_connector_tk(tokens[tk_cursor]->type))
	{
		set_next_relation(tmp, tokens[tk_cursor]);
		tk_cursor++;
		tmp->next = parse_program(tokens, &tk_cursor);
		tmp = tmp->next;
	}
	return (program);
}
