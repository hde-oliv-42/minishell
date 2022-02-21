/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:23:25 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:12 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "parsing/parsing.h"
# include "execute/execute.h"

int		cd(t_program *program, char **ms_env);
int		pwd(void);
int		env(char **ms_env);
int		echo(t_program *program);
int		export(t_program *program, char ***ms_env);
int		unset(t_program *program, char ***ms_env);
int		ms_exit(t_program *program, t_data *data);

// Utils
int		ms_env_size(char **ms_env);
int		duplicate_env(char **ms_env, char ***tmp);
void	export_error(char *str, char *err);
#endif
