/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:46:18 by psergio-          #+#    #+#             */
/*   Updated: 2022/01/25 13:26:14 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stdlib.h>

t_redirection	*parse_redirection(t_token **tokens, int *cursor)
{
	t_redirection		*redirection;
	t_redirection_type	type[TK_MAX];

	redirection = malloc(sizeof(t_redirection));
	if (redirection == NULL)
		return (NULL);
	type[TK_REDIRECT_IN_FILE] = RD_INFILE;
	type[TK_REDIRECT_IN_HEREDOC] = RD_HERE_DOC;
	type[TK_REDIRECT_OUT_APPEND] = RD_OUTFILE_APPEND;
	type[TK_REDIRECT_OUT_TRUNC] = RD_OUTFILE_TRUNC;
	redirection->type = type[tokens[*cursor]->type];
	redirection->file_name = ft_strdup(tokens[*cursor + 1]->value);
	redirection->should_expand = tokens[*cursor + 1]->should_expand;
	redirection->contents = NULL;
	(*cursor) = *cursor + 2;
	return (redirection);
}

int	add_redirection(t_program *program, t_token **tokens, int *cursor)
{
	t_redirection	*redirection;
	t_list			*new_element;
	t_list			**list;

	if (tokens[*cursor]->type == TK_REDIRECT_IN_FILE
		|| tokens[*cursor]->type == TK_REDIRECT_IN_HEREDOC)
		list = &program->input_list;
	else
		list = &program->output_list;
	redirection = parse_redirection(tokens, cursor);
	if (redirection == NULL)
		return (0);
	new_element = ft_lstnew(redirection);
	if (new_element == NULL)
		return (free(redirection), 0);
	ft_lstadd_back(list, new_element);
	return (1);
}
