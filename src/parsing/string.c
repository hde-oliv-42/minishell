/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:49:21 by psergio-          #+#    #+#             */
/*   Updated: 2021/12/28 18:50:48 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*parse_string(char *line, int *cursor)
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
	*cursor = i;
	return (str);
}
