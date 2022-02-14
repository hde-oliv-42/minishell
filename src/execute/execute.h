/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:42:14 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/29 20:23:59 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "builtins/builtins.h"
# include "parsing/parsing.h"
# include "debug/debug.h"
# include "ft_printf/libftprintf.h"
# include "signals/signals.h"

// Execute
void	execute(t_program *program_list);
void	execute_one_command(t_program *last_program, t_program *program, t_program *program_list, int *wstatus);

// Execute utils
char	**generate_argv_array(t_program *program);
void	check_pipe_relations(t_program *last_program, t_program *program);

// Environment
int		initialize_ms_env(char ***ms_env);

// Access methods
char	*find_path(char *name, char **ms_env);

// Child utils
void	check_if_must_open_stdin(t_program *last_program);
void	check_if_must_open_stdout(t_program *program);
void	open_all_output_files(t_program *program, int *out_fd);
void	open_all_input_files(t_program *program, int out_fd);

// Parent utils
void	handle_wait(t_program *program_list, int *wstatus);
void	handle_child(t_program *last_program, t_program *program, t_program *program_list, int wstatus);
void	handle_conditional_wait(int *wstatus);
int		check_conditional_error(t_program *last_program, int wstatus);

// Utils
void	command_not_found(char *program_name);
void	flush_minishell(void);
void	close_pipe(int fd[2]);

#endif
