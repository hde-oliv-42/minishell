/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:34:49 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/15 10:55:17 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <fcntl.h>
# include "tokenizer/tokenizer.h"
# include <stdio.h>

typedef struct s_program	t_program;

typedef enum e_next_relation {
	NONE,
	PIPE,
	AND,
	OR,
}	t_next_relation;

typedef enum e_program_type {
	PROGRAM,
	SUBSHELL,
}	t_program_type;

struct s_program {
	void			*name;
	int				next_pipe[2];
	t_program_type	type;
	t_list			*params;
	t_list			*input_list;
	t_list			*output_list;
	t_program		*next;
	t_next_relation	next_relation;
};

typedef enum e_redirection_type {
	RD_INFILE = O_RDONLY,
	RD_HERE_DOC,
	RD_OUTFILE_TRUNC = O_TRUNC,
	RD_OUTFILE_APPEND = O_APPEND,
}	t_redirection_type;

typedef struct s_redirection {
	t_redirection_type	type;
	char				*file_name;
	int					should_redirect;
}	t_redirection;

t_program		*parse(t_token **tokens);

void			destroy_redirection(void *content);
void			destroy_program(t_program *program);
void			destroy_pipeline(t_program *program_list);
t_redirection	*parse_redirection(t_token **tokens, int *cursor);
int				add_redirection(t_program *program,
					t_token **tokens, int *cursor);

int				make_subshell(t_program *program,
					t_token **tokens, int *cursor);

typedef struct s_string {
	char	*value;
	int		should_expand;
}	t_string;

t_string		*new_string(t_token *word);

#endif
