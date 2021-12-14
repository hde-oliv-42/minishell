/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:23:25 by hde-oliv          #+#    #+#             */
/*   Updated: 2021/12/14 20:22:21 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

void	pwd(void);

// Won't print the first argument
// Prints until a NULL
// If the first argument is not a NULL, its behavior is of "-n" flag
void	echo(char **args);
int		cd(char *path);
void	env(void);

#endif
