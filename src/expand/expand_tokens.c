/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:13:04 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/15 10:37:15 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug/debug.h"
#include "expand/expand.h"
#include "libft.h"
#include "tokenizer/tokenizer.h"

typedef struct s_token_expander {
	t_list	*last_token;
	t_list	*current_token;
	t_list	*head;
	t_token	**new_token_array;
	int		is_inside_parenthesis;
}	t_token_expander;

static t_list	*string_to_token_list(t_list *string_list)
{
	t_list	*token_list;
	t_token	*token;

	token_list = NULL;
	while (string_list)
	{
		token = new_expanded_token(TK_WORD, string_list->content);
		ft_lstadd_back(&token_list, ft_lstnew(token));
		string_list = string_list->next;
	}
	return (token_list);
}

static void	handle_asterisk(t_token_expander *expander)
{
	t_list	*next_element;
	t_list	*file_list;
	t_list	*token_list;

	next_element = (expander->current_token)->next;
	ft_lstdelone(expander->current_token, destroy_token);
	file_list = expand_asterisk();
	token_list = string_to_token_list(file_list);
	ft_lstclear(&file_list, do_nothing);
	if (expander->last_token)
		expander->last_token->next = token_list;
	else
		expander->head = token_list;
	expander->current_token = ft_lstlast(token_list);
	expander->current_token->next = next_element;
}

t_list	*token_array_to_list(t_token **token_array)
{
	t_list	*list;
	int		i;

	list = NULL;
	i = 0;
	while (token_array[i])
	{
		ft_lstadd_back(&list, ft_lstnew(token_array[i]));
		i++;
	}
	return (list);
}

void	manage_parenthesis(t_token_expander *expander)
{
	t_token	*token;

	token = expander->current_token->content;
	if (token->type == TK_OPEN_PARENTHESIS)
		expander->is_inside_parenthesis++;
	else if (token->type == TK_CLOSE_PARENTHESIS)
		expander->is_inside_parenthesis--;
}

t_token	**expand_tokens(t_token **token_array)
{
	t_token_expander	expander;
	char				*value;

	expander.is_inside_parenthesis = 0;
	expander.head = token_array_to_list(token_array);
	expander.current_token = expander.head;
	expander.last_token = NULL;
	while (expander.current_token)
	{
		manage_parenthesis(&expander);
		if (expander.is_inside_parenthesis == 0)
		{
			value = ((t_token *)expander.current_token->content)->value;
			if (ft_strncmp("*", value, 2) == 0)
				handle_asterisk(&expander);
			expander.last_token = expander.current_token;
		}
		if (expander.current_token)
			expander.current_token = expander.current_token->next;
	}
	expander.new_token_array = token_list_to_array(expander.head);
	ft_lstclear(&expander.head, do_nothing);
	return (expander.new_token_array);
}
