/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:30:47 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/06 20:48:24 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	echo(t_program *program)
{
	int	i;

	i = ft_lstsize(program->params);
	if (i == 0)
	{
		printf("\n");
		return (0);
	}
	else if (!ft_strncmp(program->params->content, "-n", 2))
	{
		if (i == 1)
			return (0);
		while (program->params->next)
		{
			program->params = program->params->next;
			printf("%s ", (char *) program->params->content);
		}
		printf("%s", (char *) program->params->content);
		return (0);
	}
	else
	{
		if (i == 1)
		{
			printf("\n");
			return (0);
		}
		while (program->params->next)
		{
			program->params = program->params->next;
			printf("%s ", (char *) program->params->content);
		}
		printf("%s\n", (char *) program->params->content);
		return (0);
	}
	return (1);
}
