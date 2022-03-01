/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:00:04 by psergio-          #+#    #+#             */
/*   Updated: 2022/01/22 18:29:43 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "ft_printf/libftprintf.h"

int	unmatched_quote(char token)
{
	ft_dprintf(2, "unmatched %c.\n", token);
	return (0);
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static char	*get_next_quote(char *line, int i)
{
	char	*next_quote;

	next_quote = NULL;
	if (line[i] == '\'')
		next_quote = ft_strchr(line + i + 1, '\'');
	else if (line[i] == '"')
		next_quote = ft_strchr(line + i + 1, '"');
	return (next_quote);
}

t_token	*get_word(char *line, int *cursor)
{
	int		i;
	char	*str;
	char	*next_quote;

	i = *cursor;
	while (!is_reserved_char(line[i]) && !is_wspace(line[i]) && line[i] != '\0')
	{
		if (is_quote(line[i]))
		{
			next_quote = NULL;
			next_quote = get_next_quote(line, i);
			if (next_quote == NULL)
				return (unmatched_quote(line[i]), NULL);
			i = next_quote - line + 1;
		}
		else
			i++;
	}
	str = ft_substr(line, *cursor, i - *cursor);
	if (str == NULL)
		return (NULL);
	*cursor = i;
	return (new_token(TK_WORD, str));
}
