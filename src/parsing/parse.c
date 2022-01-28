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

static int	handle_word(t_program *program, t_token **tokens, int *cursor)
{
	char	*word;
	t_list	*new_param;

	word = tokens[*cursor]->value;
	if (program->name == NULL)
		program->name = ft_strdup(word);
	else
	{
		new_param = ft_lstnew(ft_strdup(word));
		if (new_param == NULL)
			return (0);
		ft_lstadd_back(&program->params, new_param);
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
