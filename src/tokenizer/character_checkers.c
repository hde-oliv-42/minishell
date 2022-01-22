/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 07:19:29 by psergio-          #+#    #+#             */
/*   Updated: 2022/01/14 07:22:02 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_wspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v');
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
	return (is_redirection(c) || is_connector(c) || is_parenthesis(c));
}

int	is_word(char c)
{
	return (!is_reserved_char(c));
}
