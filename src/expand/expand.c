/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 13:44:47 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/06 14:03:03 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing/parsing.h"
#include "tokenizer/tokenizer.h"
#include "expand/expand.h"
#include <stdlib.h>

struct s_piece {
	int		len;
	char	*value;
};

typedef struct s_piece	t_piece;

static t_piece	*new_piece(char *value, int len)
{
	t_piece	*piece;

	if (value == NULL)
		return (NULL);
	piece = malloc(sizeof(t_piece));
	if (piece == NULL)
		return (NULL);
	piece->value = value;
	piece->len = len;
	return (piece);
}

char	*get_next_break_point(char current)
{
	if (current == '\'')
		return ("'");
	else if (current == '"')
		return ("\"$");
	else
		return ("\"'$");
}

static int	get_piece(t_list **piece_list, const char *str, int start, int end)
{
	t_piece	*piece;
	char	*value;

	value = ft_substr(str, start, end - start);
	if (value == NULL)
		return (0);
	piece = new_piece(value, end - start);
	if (piece == NULL)
		return (0);
	ft_lstadd_back(piece_list, ft_lstnew(piece));
	return (1);
}

static char	*merge_pieces(t_list *piece_list)
{
	t_list	*tmp;
	int		total_len;
	char	*str;

	tmp = piece_list;
	total_len = 0;
	while (tmp)
	{
		total_len += ((t_piece *)tmp->content)->len;
		tmp = tmp->next;
	}
	str = ft_calloc(total_len + 1, 1);
	if (str == NULL)
		return (NULL);
	tmp = piece_list;
	while (tmp)
	{
		ft_strlcat(str, ((t_piece *)tmp->content)->value, total_len + 1);
		tmp = tmp->next;
	}
	return (str);
}

static void	destroy_piece(void *piece)
{
	free(((t_piece *)piece)->value);
	free(piece);
}

char	*expand_word(const char *word)
{
	int		start;
	int		end;
	char	*str;
	char	inside_quote;
	t_list	*piece_list;

	start = 0;
	end = -1;
	piece_list = NULL;
	inside_quote = '\0';
	while (word[++end])
	{
		if (word[end] == '\'' && inside_quote != '"')
		{
			get_piece(&piece_list, word, start, end);
			if (!inside_quote)
				inside_quote = '\'';
			else
				inside_quote = '\0';
			start = end + 1;
		}
		else if (word[end] == '"' && inside_quote != '\'')
		{
			get_piece(&piece_list, word, start, end);
			if (!inside_quote)
				inside_quote = '"';
			else
				inside_quote = '\0';
			start = end + 1;
		}
	}
	if (end > start)
		get_piece(&piece_list, word, start, end);
	str = merge_pieces(piece_list);
	ft_lstclear(&piece_list, destroy_piece);
	return (str);
}

void	expand_words(t_program *programs)
{
	while (programs)
	{
		programs->name = expand_word(programs->name);
	}
}
