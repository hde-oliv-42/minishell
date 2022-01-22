/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 07:50:07 by psergio-          #+#    #+#             */
/*   Updated: 2022/01/14 07:55:40 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdio.h>

t_token	*new_token(t_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = value;
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

t_token	*get_word(char *line, int *cursor)
{
	int		i;
	char	*str;
	char	*next_quote;

	i = *cursor;
	while (!is_reserved_char(line[i]) && !is_wspace(line[i]) && line[i] != '\0')
	{
		next_quote = NULL;
		if (line[i] == '\'')
			next_quote = ft_strchr(line + i + 1, '\'');
		else if (line[i] == '"')
			next_quote = ft_strchr(line + i + 1, '"');
		if (next_quote != NULL)
			i = next_quote - line + 1;
		else
			i++;
	}
	str = ft_substr(line, *cursor, i - *cursor);
	if (str == NULL)
		return (NULL);
	*cursor = i;
	return (new_token(TK_WORD, str));
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
