/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 17:04:01 by psergio-          #+#    #+#             */
/*   Updated: 2021/12/30 17:04:30 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	destroy_string(void *content)
{
	t_string	*string;

	string = content;
	free(string->value);
	free(string);
}

void	destroy_redirection(void *content)
{
	t_redirection	*redirection;

	redirection = content;
	free(redirection->file_name);
	free(redirection);
}

void	do_nothing(void *content)
{
	(void)content;
}

void	destroy_program(t_program *program)
{
	destroy_string(program->name);
	ft_lstclear(&program->params, destroy_string);
	ft_lstclear(&program->input_list, destroy_redirection);
	ft_lstclear(&program->output_list, destroy_redirection);
	free(program);
}

void	destroy_pipeline(t_program *program_list)
{
	t_program	*tmp;

	tmp = program_list;
	while (program_list)
	{
		tmp = program_list->next;
		destroy_program(program_list);
		program_list = tmp;
	}
}
