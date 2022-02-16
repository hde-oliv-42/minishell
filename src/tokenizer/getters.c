/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 07:50:07 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/15 10:35:36 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdio.h>

t_token	*new_expanded_token(t_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = value;
	token->should_expand = 0;
	return (token);
}

t_token	*new_token(t_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = value;
	token->should_expand = 1;
	return (token);
}

t_token	*get_redirection(char *line, int *cursor)
{
	if (line[*cursor] == '>')
	{
		(*cursor)++;
		if (line[*cursor] == '>')
		{
			(*cursor)++;
			return (new_token(TK_REDIRECT_OUT_APPEND, ">>"));
		}
		else
			return (new_token(TK_REDIRECT_OUT_TRUNC, ">"));
	}
	else
	{
		(*cursor)++;
		if (line[*cursor] == '<')
		{
			(*cursor)++;
			return (new_token(TK_REDIRECT_IN_HEREDOC, "<<"));
		}
		else
			return (new_token(TK_REDIRECT_IN_FILE, "<"));
	}
}

t_token	*get_connector(char *line, int *cursor)
{
	if (line[*cursor] == '|')
	{
		(*cursor)++;
		if (line[*cursor] == '|')
		{
			(*cursor)++;
			return (new_token(TK_OR, "||"));
		}
		else
			return (new_token(TK_PIPE, "|"));
	}
	else if (line[*cursor] == '&' && line[*cursor + 1] == '&')
	{
		(*cursor) += 2;
		return (new_token(TK_AND, "&&"));
	}
	else
	{
		printf("unrecognized token %c\n", line[*cursor]);
		return (NULL);
	}
}

t_token	*get_parenthesis(char *line, int *cursor)
{
	if (line[(*cursor)++] == '(')
		return (new_token(TK_OPEN_PARENTHESIS, "("));
	else
		return (new_token(TK_CLOSE_PARENTHESIS, ")"));
}
