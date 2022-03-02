/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:26:04 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/19 15:30:41 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <libft.h>
# include <fcntl.h>

typedef enum e_program_type {
	PROGRAM,
	SUBSHELL,
}	t_program_type;

typedef struct s_string {
	char	*value;
	int		should_expand;
}	t_string;

typedef enum e_redirection_type {
	RD_INFILE = O_RDONLY,
	RD_HERE_DOC,
	RD_OUTFILE_TRUNC = O_TRUNC,
	RD_OUTFILE_APPEND = O_APPEND,
}	t_redirection_type;

typedef struct s_redirection {
	t_redirection_type	type;
	char				*file_name;
	int					should_expand;
	char				*contents;
}	t_redirection;

typedef enum e_next_relation {
	NONE,
	PIPE,
	AND,
	OR,
}	t_next_relation;

typedef struct s_program	t_program;

struct s_program {
	t_string		*name;
	int				next_pipe[2];
	t_program_type	type;
	int				pid;
	int				ret;
	t_list			*params;
	t_list			*input_list;
	t_list			*output_list;
	t_program		*next;
	t_next_relation	next_relation;
};

typedef struct s_data
{
	t_program	*program_list;
	t_program	*program;
	t_program	*last_program;
	int			program_count;
	int			wstatus;
	char		*cwd;
	int			must_continue;
	int			og_fd[2];
}	t_data;

#endif /* !STRUCTURES_H */
