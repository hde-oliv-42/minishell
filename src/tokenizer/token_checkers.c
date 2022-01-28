/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:40:08 by psergio-          #+#    #+#             */
/*   Updated: 2022/01/22 17:49:57 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_redirection_tk(t_type type)
{
	return (type == TK_REDIRECT_IN_FILE
		|| type == TK_REDIRECT_IN_HEREDOC
		|| type == TK_REDIRECT_OUT_APPEND
		|| type == TK_REDIRECT_OUT_TRUNC);
}

int	is_connector_tk(t_type type)
{
	return (type == TK_AND || type == TK_OR || type == TK_PIPE);
}

int	is_word_tk(t_type type)
{
	return (type == TK_WORD);
}

int	is_parenthesis_tk(t_type type)
{
	return (type == TK_OPEN_PARENTHESIS || type == TK_CLOSE_PARENTHESIS);
}
