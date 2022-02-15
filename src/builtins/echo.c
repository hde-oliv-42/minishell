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

static int	handle_n_option(t_program *tmp, int i)
{
	if (i == 1)
		return (0);
	tmp->params = tmp->params->next;
	while (tmp->params->next)
	{
		printf("%s ", (char *) tmp->params->content);
		tmp->params = tmp->params->next;
	}
	printf("%s", (char *) tmp->params->content);
	return (0);
}

static int	handle_no_option(t_program *tmp)
{
	while (tmp->params->next)
	{
		printf("%s ", (char *) tmp->params->content);
		tmp->params = tmp->params->next;
	}
	printf("%s\n", (char *) tmp->params->content);
	return (0);
}

int	echo(t_program *program)
{
	int			i;
	t_program	*tmp;

	i = ft_lstsize(program->params);
	tmp = program;
	if (i == 0)
	{
		printf("\n");
		return (0);
	}
	else if (!ft_strncmp(tmp->params->content, "-n", 2))
		return (handle_n_option(tmp, i));
	else
		return (handle_no_option(tmp));
	return (1);
}
