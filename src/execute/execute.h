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
# include <errno.h>
# include "libft.h"
# include "builtins/builtins.h"
# include "parsing/parsing.h"
# include "debug/debug.h"
# include "ft_printf/libftprintf.h"
# include "signals/signals.h"
# include "heredoc/heredoc.h"

extern char	**g_env;

typedef struct s_data
{
	t_program	*program_list;
	t_program	*program;
	t_program	*last_program;
	int			program_count;
	int			*wstatus;
}	t_data;

// Execute
void	execute(t_program *program_list);
void	execute_one_command(t_data *data);

// Execute builtin
int		is_builtin(t_data *data);
int		execute_builtin(t_data *data, int id);

// Execute utils
char	**generate_argv_array(t_program *program);
void	check_pipe_relations(t_data *data);
void	command_not_found(char *program_name);
void	flush_minishell(t_data *data);
void	close_pipe(int fd[2], t_data *data);

// Environment
int		initialize_ms_env(char ***ms_env);

// Access methods
char	*find_path(char *name, char **ms_env);
int		is_writable(char *path);
int		is_readable(char *path);
int		is_executable(char *path);

// Access utils
int		create_path_array(char *path_string, char ***path_array);
void	free_path_array(char **path_array);
void	fetch_path_string(char **ms_env, char **path_string);
char	*loop_path_array(char *name, char **path_array);

// Child utils
void	check_if_must_open_stdin(t_data *data);
void	check_if_must_open_stdout(t_data *data);
void	open_all_output_files(t_data *data);
void	open_all_input_files(t_data *data);

// Parent utils
void	handle_wait(t_data *data);
void	handle_child(t_data *data);
void	handle_conditional_wait(t_data *data);
int		check_conditional_error(t_data *data);

#endif
