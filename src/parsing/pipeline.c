/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:34:27 by psergio-          #+#    #+#             */
/*   Updated: 2021/12/28 18:50:48 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_param(t_program *program, char *line, int *cursor)
{
	char	*param;

	param = parse_string(line, cursor);
	ft_lstadd_back(&program->params, ft_lstnew(param));
}

t_program	*parse_program(char *line, int *cursor)
{
	t_program	*program;

	skip_spaces(line, cursor);
	if (line[*cursor] == '\0')
		return (NULL);
	program = ft_calloc(1, sizeof(t_program));
	if (program == NULL)
		exit(2);
	while (!is_connector(line[*cursor]) && line[*cursor] != '\0')
	{
		if (is_redirection(line[*cursor]))
			parse_redirection(program, line, cursor);
		else if (program->name == NULL)
			program->name = parse_string(line, cursor);
		else
			parse_param(program, line, cursor);
		skip_spaces(line, cursor);
	}
	return (program);
}

void	set_connection_type(t_program *program, char *line, int *cursor)
{
	if (line[*cursor] == '|')
	{
		if (line[*cursor + 1] == '|')
		{
			(*cursor)++;
			program->next_relation = OR;
		}
		else
			program->next_relation = PIPE;
	}
	else
	{
		(*cursor)++;
		program->next_relation = AND;
	}
	(*cursor)++;
}

t_program	*parse_pipeline(char *line, int *cursor)
{
	t_program	*program;
	t_program	*tmp;

	program = parse_program(line, cursor);
	tmp = program;
	while (is_connector(line[*cursor]) && line[*cursor] != '\0')
	{
		set_connection_type(tmp, line, cursor);
		tmp->next = parse_program(line, cursor);
		tmp = tmp->next;
	}
	return (program);
}
