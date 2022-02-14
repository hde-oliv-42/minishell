/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/03 20:32:53 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	command_not_found(char *program_name)
{
	ft_dprintf(2, "minishell: %s: command not found\n", program_name);
}

void	flush_minishell(t_data *data)
{
	(void)data;
	exit(errno);
}

void	close_pipe(int fd[2], t_data *data)
{
	if (close(fd[0]))
		flush_minishell(data);
	if (close(fd[1]))
		flush_minishell(data);
}

void	free_minishell(t_data *data)
{
	(void)data;
}
