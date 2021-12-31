/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:42:00 by psergio-          #+#    #+#             */
/*   Updated: 2021/12/28 18:19:55 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_wspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v');
}

void	skip_spaces(char *line, int *cursor)
{
	while (is_wspace(line[*cursor]))
		(*cursor)++;
}

int	is_connector(char c)
{
	return (!!ft_strchr("&|", c));
}

int	is_redirection(char c)
{
	return (!!ft_strchr("><", c));
}

int	is_reserved_char(char c)
{
	return (is_redirection(c) || is_connector(c));
}
