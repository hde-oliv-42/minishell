/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_methods.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:42:21 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/05 20:27:48 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

void	lstdelone(t_lst *lst, void (*del)(void *))
{
	(*del)(lst->data);
	(*del)(lst->key);
	free(lst);
}

void	lstclear(t_lst **lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (*lst)
	{
		lstclear(&(*lst)->next, del);
		(*del)((*lst)->data);
		(*del)((*lst)->key);
		free(*lst);
		*lst = NULL;
	}
}

t_lst	*lstlast(t_lst *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = lstlast((*lst));
	last->next = new;
}

t_lst	*lstnew(void *key, void *data)
{
	t_lst	*a;

	a = (t_lst *) malloc(sizeof(t_lst) * 1);
	if (!a)
		return (NULL);
	a->data = data;
	a->key = key;
	a->next = NULL;
	return (a);
}
