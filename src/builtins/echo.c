/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:30:47 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:17 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "parsing/parsing.h"
#include "structures.h"

int	echo(t_program *program)
{
	int			printnl;
	char		*str;
	t_list		*tmp;

	tmp = program->params;
	printnl = 1;
	while (tmp && str_equals(((t_string *)tmp->content)->value, "-n"))
	{
		printnl = 0;
		tmp = tmp->next;
	}
	while (tmp)
	{
		str = ((t_string *)tmp->content)->value;
		printf("%s", str);
		if (tmp->next)
			printf(" ");
		tmp = tmp->next;
	}
	if (printnl)
		printf("\n");
	return (0);
}
