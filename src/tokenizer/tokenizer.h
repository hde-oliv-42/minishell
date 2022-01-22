/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 07:57:41 by psergio-          #+#    #+#             */
/*   Updated: 2022/01/16 13:24:11 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <libft.h>

enum e_token_type {
	TK_WORD,
	TK_OPEN_PARENTHESIS,
	TK_CLOSE_PARENTHESIS,
	TK_REDIRECT_OUT_TRUNC,
	TK_REDIRECT_OUT_APPEND,
	TK_REDIRECT_IN_FILE,
	TK_REDIRECT_IN_HEREDOC,
	TK_AND,
	TK_OR,
	TK_PIPE,
	TK_MAX,
};

typedef enum e_token_type	t_type;

struct s_token {
	t_type	type;
	char	*value;
};

typedef struct s_token		t_token;

/* functions in tokenize.c */

t_token	**tokenize(char *line);
void	destroy_token(void *content);

/* functions in checkers*.c */
int		is_wspace(char c);
int		is_connector(char c);
int		is_redirection(char c);
int		is_reserved_char(char c);
int		is_word(char c);
int		is_parenthesis(char c);

/* functions in destroy_tokens.c */
void	destroy_token(void *content);
void	keep_token(void *content);
void	destroy_token_array(t_token **tokens);
int		clear_tokens(t_list *tokens);

/* functions in getters.c */
t_token	*get_redirection(char *line, int *cursor);
t_token	*get_word(char *line, int *cursor);
t_token	*get_connector(char *line, int *cursor);
t_token	*get_parenthesis(char *line, int *cursor);

/* functions in validator*.c */
int		validate_tokens(t_token **tokens);
int		validate_last(t_token *token);
int		unexpected_token(char *token);

#endif
