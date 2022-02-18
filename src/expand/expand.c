/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:44:47 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/16 12:45:12 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand/expand.h"
#include "execute/execute.h"
#include "libft.h"
#include "parsing/parsing.h"
#include "execute/ms_env.h"

#define VAR_DELIMITERS "\"'$ =@(*)#"

static int	skip_dollar(t_list **piece_list, char chr)
{
	char	*delimiters;
	t_piece	*piece;
	char	*value;

	delimiters = "$ =@(*)#";
	value = malloc(3);
	value[0] = '$';
	if (ft_strchr(delimiters, chr))
		value[1] = chr;
	else
		value[1] = '\0';
	value[2] = '\0';
	piece = new_piece(value, ft_strlen(value));
	ft_lstadd_back(piece_list, ft_lstnew(piece));
	return (1);
}

static char	*get_last_status(t_data *data)
{
	char	*status_str;

	status_str = ft_itoa(*data->wstatus);
	if (status_str == NULL)
	{
		perror("error getting last status");
		return (NULL);
	}
	return (status_str);
}

static int	get_env_variable(
		t_list **piece_list, const char *str, int *size, t_data *data)
{
	char	*delimiters;
	char	*key;
	char	*value;
	t_piece	*piece;

	delimiters = VAR_DELIMITERS;
	(*size)++;
	if (ft_strchr(delimiters, str[*size]))
		return (skip_dollar(piece_list, str[*size]));
	while (!ft_strchr(delimiters, str[*size]))
		(*size)++;
	key = ft_substr(str, 0, *size);
	(*size)--;
	if (str_equals(key, "?"))
		value = get_last_status(data);
	else
		value = search_env(key);
	if (value == NULL)
		value = ft_strdup("");
	free(key);
	piece = new_piece(value, ft_strlen(value));
	ft_lstadd_back(piece_list, ft_lstnew(piece));
	return (1);
}

void	extract_until_quote(
		t_list **piece_list, char **word, char *inside_quote, int *size)
{
	char	quote;

	quote = (*word)[*size];
	get_piece(piece_list, *word, *size);
	if (!*inside_quote)
		*inside_quote = quote;
	else
		*inside_quote = '\0';
	*word += *size + 1;
	*size = -1;
}

typedef struct s_expander
{
	t_list	*piece_list;
	char	*word;
	char	inside_quote;
}	t_expander;

void	try_get_piece(
		t_expander *expander, char *inside_quote, int *size, t_data *data)
{
	char	**word;
	t_list	**piece_list;

	word = &expander->word;
	piece_list = &expander->piece_list;
	if ((*word)[*size] == '\'' && *inside_quote != '"')
		extract_until_quote(piece_list, word, inside_quote, size);
	else if ((*word)[*size] == '"' && *inside_quote != '\'')
		extract_until_quote(piece_list, word, inside_quote, size);
	else if ((*word)[*size] == '$' && *inside_quote != '\'')
	{
		get_piece(piece_list, *word, *size);
		*word += *size + 1;
		*size = -1;
		get_env_variable(piece_list, *word, size, data);
		*word += *size + ((*word)[*size] != '\0');
		*size = -1;
	}
}

char	*expand_word(char *word, t_data *data)
{
	int			size;
	char		*str;
	char		inside_quote;
	t_expander	expander;

	expander.piece_list = NULL;
	expander.inside_quote = '\0';
	expander.word = word;
	size = -1;
	inside_quote = '\0';
	while (word[++size])
	{
		try_get_piece(&expander, &inside_quote, &size, data);
	}
	if (size > 0)
		get_piece(&expander.piece_list, expander.word, size);
	str = merge_pieces(expander.piece_list);
	ft_lstclear(&expander.piece_list, destroy_piece);
	return (str);
}

void	expand_redirections(t_list *list, t_data *data)
{
	t_list			*cursor;
	t_redirection	*redirection;
	char			*new_str;

	cursor = list;
	while (cursor)
	{
		redirection = cursor->content;
		if (redirection->should_redirect)
		{
			new_str = expand_word(redirection->file_name, data);
			free(redirection->file_name);
			redirection->file_name = new_str;
		}
		cursor = cursor->next;
	}
}

void	expand_program(t_program *program, t_data *data)
{
	char		*tmp;
	t_list		*tmp_list;
	t_string	*tmp_string;

	if (program->name && program->name->should_expand)
	{
		tmp = program->name->value;
		program->name->value = expand_word(tmp, data);
		free(tmp);
	}
	tmp_list = program->params;
	while (program->type != SUBSHELL && tmp_list)
	{
		if (((t_string *)tmp_list->content)->should_expand)
		{
			tmp_string = tmp_list->content;
			tmp = tmp_string->value;
			tmp_string->value = expand_word(tmp, data);
			free(tmp);
		}
		tmp_list = tmp_list->next;
	}
	expand_redirections(program->input_list, data);
	expand_redirections(program->output_list, data);
}
