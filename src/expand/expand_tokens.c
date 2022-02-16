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

static void	handle_asterisk(t_list **head, t_list **cursor, t_list *last_token)
{
	t_list	*next_element;
	t_list	*file_list;
	t_list	*token_list;

	next_element = (*cursor)->next;
	ft_lstdelone(*cursor, destroy_token);
	file_list = expand_asterisk();
	token_list = string_to_token_list(file_list);
	ft_lstclear(&file_list, do_nothing);
	if (last_token)
		last_token->next = token_list;
	else
		*head = token_list;
	*cursor = ft_lstlast(token_list);
	(*cursor)->next = next_element;
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

t_token	**expand_tokens(t_token **token_array)
{
	char	*value;
	t_list	*last_token;
	t_list	*token;
	t_list	*head;
	t_token	**new_token_array;

	head = token_array_to_list(token_array);
	token = head;
	last_token = NULL;
	while (token)
	{
		value = ((t_token *)token->content)->value;
		if (ft_strncmp("*", value, 2) == 0)
			handle_asterisk(&head, &token, last_token);
		last_token = token;
		if (token)
			token = token->next;
	}
	new_token_array = token_list_to_array(head);
	ft_lstclear(&head, do_nothing);
	return (new_token_array);
}
