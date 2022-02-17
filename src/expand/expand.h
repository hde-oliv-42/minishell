/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:43:30 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/11 16:32:24 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <parsing/parsing.h>
# include "execute/execute.h"
# include "libft.h"
# include "parsing/parsing.h"
# include "tokenizer/tokenizer.h"
# include <stdlib.h>
# include <stdlib.h>

struct s_piece {
	int		len;
	char	*value;
};

typedef struct s_piece	t_piece;

void	expand_words(t_program *programs);
char	*expand_word(char *word, t_data *data);
t_piece	*new_piece(char *value, int len);
int		get_piece(t_list **piece_list, const char *str, int size);
char	*merge_pieces(t_list *piece_list);
void	destroy_piece(void *piece);
t_list	*expand_asterisk(void);

t_token	**expand_tokens(t_token **token_array);
void	expand_program(t_program *program, t_data *data);

#endif
