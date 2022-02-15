/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/03 20:32:53 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_builtin(t_data *data)
{
	if (data->program->name == NULL)
		return (0);
	else if (!ft_strncmp(data->program->name, "cd", 3))
		return (1);
	else if (!ft_strncmp(data->program->name, "echo", 5))
		return (2);
	else if (!ft_strncmp(data->program->name, "export", 7))
		return (3);
	else if (!ft_strncmp(data->program->name, "unset", 6))
		return (4);
	else if (!ft_strncmp(data->program->name, "env", 4))
		return (5);
	else if (!ft_strncmp(data->program->name, "pwd", 4))
		return (6);
	return (0);
}

int	execute_builtin(t_data *data, int id)
{
	if (id == 0)
		return (-1);
	if (id == 1)
		*(data->wstatus) = cd(data->program, g_env);
	else if (id == 2)
		*(data->wstatus) = echo(data->program);
	else if (id == 3)
		*(data->wstatus) = export(data->program, &g_env);
	else if (id == 4)
		*(data->wstatus) = unset(data->program, &g_env);
	else if (id == 5)
		env(g_env);
	else if (id == 6)
		*(data->wstatus) = pwd();
	else
		*(data->wstatus) = 0;
	data->last_program = data->program;
	data->program = data->program->next;
	return (*(data->wstatus));
}