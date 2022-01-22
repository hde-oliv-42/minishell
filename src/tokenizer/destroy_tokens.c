/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 07:23:04 by psergio-          #+#    #+#             */
/*   Updated: 2022/01/14 07:23:13 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	destroy_token(void *content)
{
	t_token	*token;

	token = content;
	if (token->type == TK_WORD)
		free(token->value);
	free(token);
}

void	keep_token(void *content)
{
	(void)content;
}

int	clear_tokens(t_list *tokens)
{
	ft_lstclear(&tokens, destroy_token);
	return (0);
}

void	destroy_token_array(t_token **tokens)
{
	t_token	**array;

	array = tokens;
	while (*tokens)
		destroy_token(*tokens++);
	free(array);
}
