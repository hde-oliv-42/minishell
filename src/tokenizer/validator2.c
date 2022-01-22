/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 13:11:21 by psergio-          #+#    #+#             */
/*   Updated: 2022/01/22 17:44:31 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdio.h>

int	unexpected_token(char *token)
{
	printf("validation error: unexpected token '%s'\n", token);
	return (0);
}

int	validate_last(t_token *token)
{
	if (token->type == TK_WORD)
		return (1);
	if (token->type == TK_CLOSE_PARENTHESIS)
		return (1);
	return (unexpected_token("end of line"));
}

int	validate_first(t_token *token)
{
	if (
		token->type == TK_AND
		|| token->type == TK_OR
		|| token->type == TK_PIPE
		|| (token->type == TK_CLOSE_PARENTHESIS))
	{
		return (unexpected_token(token->value));
	}
	return (1);
}

int	count_parenthesis(t_token **tokens)
{
	int	i;
	int	unclosed_parenthesis;

	i = 0;
	unclosed_parenthesis = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == TK_OPEN_PARENTHESIS)
			unclosed_parenthesis++;
		else if (tokens[i]->type == TK_CLOSE_PARENTHESIS)
			unclosed_parenthesis--;
		if (unclosed_parenthesis < 0)
			return (unexpected_token(")"));
		i++;
	}
	if (unclosed_parenthesis != 0)
		return (unexpected_token("end of line"));
	return (1);
}

int	validate_after_word(t_token *next)
{
	if (next == NULL)
		return (1);
	if (next->type == TK_OPEN_PARENTHESIS)
		return (unexpected_token(next->value));
	return (1);
}
