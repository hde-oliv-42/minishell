/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:22:59 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/15 15:27:10 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug/debug.h"
#include "libft.h"
#include <stdlib.h>
#include <parsing/parsing.h>
#include <tokenizer/tokenizer.h>
#include <expand/expand.h>

t_token	*get_next_token(char *line, int *cursor)
{
	t_token	*token;
	char	character;

	token = NULL;
	character = line[*cursor];
	if (is_redirection(character))
		token = get_redirection(line, cursor);
	else if (is_connector(character))
		token = get_connector(line, cursor);
	else if (is_parenthesis(character))
		token = get_parenthesis(line, cursor);
	else if (is_word(character))
		token = get_word(line, cursor);
	return (token);
}

int	get_tokens(t_list **tokens, char *line)
{
	t_token	*token;
	int		cursor;

	cursor = 0;
	while (line[cursor])
	{
		if (is_wspace(line[cursor]))
			cursor++;
		else
		{
			token = get_next_token(line, &cursor);
			if (token == NULL)
				return (clear_tokens(*tokens));
			else
				ft_lstadd_back(tokens, ft_lstnew(token));
		}
	}
	return (1);
}

t_token	**token_list_to_array(t_list *tokens)
{
	t_token	**token_arr;
	int		size;
	int		i;

	size = ft_lstsize(tokens);
	if (size == 0)
		return (NULL);
	token_arr = malloc(sizeof(**token_arr) * (size + 1));
	if (token_arr == NULL)
		return (NULL);
	token_arr[size] = NULL;
	i = 0;
	while (i < size)
	{
		token_arr[i] = tokens->content;
		tokens = tokens->next;
		i++;
	}
	return (token_arr);
}

t_token	**tokenize(char *line)
{
	t_token	**tokens;
	t_token	**expanded_tokens;
	t_list	*token_list;
	int		valid;

	token_list = NULL;
	if (get_tokens(&token_list, line))
	{
		tokens = token_list_to_array(token_list);
		print_tokens(tokens);
		if (tokens == NULL)
			return (NULL);
		ft_lstclear(&token_list, keep_token);
		valid = validate_tokens(tokens);
		if (valid == 0)
		{
			destroy_token_array(tokens);
			return (NULL);
		}
		expanded_tokens = expand_tokens(tokens);
		printf("expanded tokens: \n");
		print_tokens(expanded_tokens);
		free(tokens);
		return (expanded_tokens);
	}
	return (NULL);
}
