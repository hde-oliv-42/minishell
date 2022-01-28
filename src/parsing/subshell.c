/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:58:48 by psergio-          #+#    #+#             */
/*   Updated: 2022/01/25 13:38:51 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "tokenizer/tokenizer.h"

static char	*merge_strings(char *str1, char *str2)
{
	char	*str;
	char	*tmp;

	if (str1 == NULL)
		tmp = ft_strdup(str2);
	else
		tmp = ft_strjoin(str1, str2);
	if (tmp == NULL)
		return (NULL);
	str = ft_strjoin(tmp, " ");
	free(tmp);
	return (str);
}

static char	*get_param(t_token **tokens, int *cursor)
{
	char	*param;
	char	*tmp;
	int		open_parenthesis;

	(*cursor)++;
	param = NULL;
	open_parenthesis = 1;
	while (open_parenthesis)
	{
		if (tokens[*cursor]->type == TK_OPEN_PARENTHESIS)
			open_parenthesis++;
		else if (tokens[*cursor]->type == TK_CLOSE_PARENTHESIS)
			open_parenthesis--;
		if (tokens[*cursor]->type == TK_CLOSE_PARENTHESIS && !open_parenthesis)
			break ;
		tmp = merge_strings(param, tokens[*cursor]->value);
		free(param);
		param = tmp;
		(*cursor)++;
	}
	(*cursor)++;
	return (param);
}

int	make_subshell(t_program *program, t_token **tokens, int *cursor)
{
	char	*param;

	program->name = ft_strdup("subshell");
	program->type = SUBSHELL;
	param = get_param(tokens, cursor);
	if (param == NULL)
		return (0);
	ft_lstadd_back(&program->params, ft_lstnew(param));
	return (1);
}
