/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 13:11:21 by psergio-          #+#    #+#             */
/*   Updated: 2022/01/16 13:24:38 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer/tokenizer.h"
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
