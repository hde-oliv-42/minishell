/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:34:49 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/19 15:29:41 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <fcntl.h>
# include "tokenizer/tokenizer.h"
# include <stdio.h>

# include <structures.h>

t_program		*parse(t_token **tokens);

void			destroy_redirection(void *content);
void			destroy_program(t_program *program);
void			destroy_pipeline(t_program *program_list);
t_redirection	*parse_redirection(t_token **tokens, int *cursor);
int				add_redirection(t_program *program,
					t_token **tokens, int *cursor);

int				make_subshell(t_program *program,
					t_token **tokens, int *cursor);

t_string		*new_string(t_token *word);

#endif
