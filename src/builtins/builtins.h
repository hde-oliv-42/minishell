/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:23:25 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/06 20:49:31 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "parsing/parsing.h"

int		cd(t_program *program, char **ms_env);
int		pwd(void);
void	env(char **ms_env);
int		echo(t_program *program);
int		export(t_program *program, char **ms_env);
int		unset(t_program *program, char **ms_env);

#endif
