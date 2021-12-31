/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:46:18 by psergio-          #+#    #+#             */
/*   Updated: 2021/12/28 18:50:48 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stdlib.h>

char	*get_filename(char *line, int *cursor)
{
	char	*filename;

	skip_spaces(line, cursor);
	filename = parse_string(line, cursor);
	return (filename);
}

static void	parse_redirection_internal(t_list **list_to_append,
		char *line, int *cursor, t_redirection_type type)
{
	char			*file_name;
	t_redirection	*redirection;

	(*cursor)++;
	if (type == OUTFILE_APPEND || type == HERE_DOC)
		(*cursor)++;
	redirection = malloc(sizeof(t_redirection));
	if (redirection == NULL)
		return ;
	file_name = get_filename(line, cursor);
	if (file_name == NULL)
		return ;
	redirection->file_name = file_name;
	redirection->type = type;
	ft_lstadd_back(list_to_append, ft_lstnew(redirection));
}

void	parse_redirection(t_program *program, char *line, int *cursor)
{
	t_list	**list;

	if (line[*cursor] == '<')
	{
		list = &program->input_list;
		if (line[*cursor + 1] == '<')
			parse_redirection_internal(list, line, cursor, HERE_DOC);
		else
			parse_redirection_internal(list, line, cursor, INFILE);
	}
	else
	{
		list = &program->output_list;
		if (line[*cursor + 1] == '>')
			parse_redirection_internal(list, line, cursor, OUTFILE_APPEND);
		else
			parse_redirection_internal(list, line, cursor, OUTFILE_TRUNC);
	}
}
