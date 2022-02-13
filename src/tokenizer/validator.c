/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 11:25:07 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/13 16:27:45 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <fcntl.h>

static int	validate_after_parenthesis(char *value, t_token *next)
{
	if (*value == '(')
	{
		if (next == NULL)
			return (unexpected_token("end of line"));
		if (*next->value == ')')
			return (unexpected_token(")"));
		if (next->type == TK_AND
			|| next->type == TK_OR || next->type == TK_PIPE)
			return (unexpected_token(next->value));
		return (1);
	}
	else
	{
		if (next == NULL)
			return (1);
		if (*next->value == ')')
			return (1);
		if (next->type == TK_AND
			|| next->type == TK_OR || next->type == TK_PIPE)
			return (1);
		if (is_redirection_tk(next->type))
			return (1);
		return (unexpected_token(next->value));
	}
}

static int	validate_after_redirection(t_token *next)
{
	if (next == NULL)
		return (unexpected_token("end of line"));
	if (next->type != TK_WORD)
		return (unexpected_token(next->value));
	return (1);
}

static int	validate_after_connector(t_token *next)
{
	if (next == NULL)
		return (unexpected_token("end of line"));
	if (next->type == TK_CLOSE_PARENTHESIS)
		return (unexpected_token(next->value));
	if (is_connector_tk(next->type))
		return (unexpected_token(next->value));
	return (1);
}

static int	validate_next(t_token **tokens, int i)
{
	t_token	*current;
	t_token	*next;

	current = tokens[i];
	next = tokens[i + 1];
	if (is_parenthesis_tk(current->type))
		return (validate_after_parenthesis(current->value, next));
	if (is_redirection_tk(current->type))
		return (validate_after_redirection(next));
	if (is_connector_tk(current->type))
		return (validate_after_connector(next));
	if (is_word_tk(current->type))
		return (validate_after_word(next));
	return (1);
}

int	validate_tokens(t_token **tokens)
{
	int	i;
	int	valid;

	i = 0;
	if (!validate_first(tokens[0]))
		return (0);
	if (!count_parenthesis(tokens))
		return (0);
	valid = 1;
	while (tokens[i] != NULL)
	{
		valid = validate_next(tokens, i);
		if (valid == 0)
			return (0);
		i++;
	}
	valid = validate_last(tokens[i - 1]);
	return (valid);
}
