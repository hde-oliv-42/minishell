/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:44:47 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/13 16:31:14 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand/expand.h"
#include "libft.h"
#include "parsing/parsing.h"

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

static int	get_env_variable(
		t_list **piece_list, const char *str, int *size)
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
	if (ft_strncmp("USER", key, 5) == 0)
		value = ft_strdup("paulo");
	else
		value = ft_strdup("[none]");
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

void	try_get_piece(
		t_list **piece_list, char **word, char *inside_quote, int *size)
{
	if ((*word)[*size] == '\'' && *inside_quote != '"')
		extract_until_quote(piece_list, word, inside_quote, size);
	else if ((*word)[*size] == '"' && *inside_quote != '\'')
		extract_until_quote(piece_list, word, inside_quote, size);
	else if ((*word)[*size] == '$' && *inside_quote != '\'')
	{
		get_piece(piece_list, *word, *size);
		*word += *size + 1;
		*size = -1;
		get_env_variable(piece_list, *word, size);
		*word += *size + ((*word)[*size] != '\0');
		*size = -1;
	}
}

char	*expand_word(char *word)
{
	int		size;
	char	*str;
	char	inside_quote;
	t_list	*piece_list;

	size = -1;
	piece_list = NULL;
	inside_quote = '\0';
	while (word[++size])
	{
		try_get_piece(&piece_list, &word, &inside_quote, &size);
	}
	if (size > 0)
		get_piece(&piece_list, word, size);
	str = merge_pieces(piece_list);
	ft_lstclear(&piece_list, destroy_piece);
	return (str);
}

void	expand_redirections(t_list *list)
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
			new_str = expand_word(redirection->file_name);
			free(redirection->file_name);
			redirection->file_name = new_str;
		}
		cursor = cursor->next;
	}
}

void	expand_program(t_program *program)
{
	char		*tmp;
	t_list		*tmp_list;
	t_string	*tmp_string;

	if (program->name->should_expand)
	{
		tmp = program->name->value;
		program->name->value = expand_word(tmp);
		free(tmp);
	}
	tmp_list = program->params;
	while (tmp_list)
	{
		if (((t_string *)tmp_list->content)->should_expand)
		{
			tmp_string = tmp_list->content;
			tmp = tmp_string->value;
			tmp_string->value = expand_word(tmp);
			free(tmp);
		}
		tmp_list = tmp_list->next;
	}
	expand_redirections(program->input_list);
	expand_redirections(program->output_list);
}
