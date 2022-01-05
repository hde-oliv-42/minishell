/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:00:09 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/05 20:27:05 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include <stdio.h>

int	ht_init(t_ht *ht, int buckets, unsigned int (*h)(void *k))
{
	ht->table = (t_lst **)ft_calloc(buckets, sizeof(t_lst *));
	if (ht->table == NULL)
		return (-1);
	ht->buckets = buckets;
	while (--buckets != -1)
		lstadd_back(&ht->table[buckets], lstnew(NULL, NULL));
	ht->h = h;
	return (0);
}

void	ht_destroy(t_ht *ht)
{
	int	i;

	i = 0;
	while (i != ht->buckets)
		lstclear(&ht->table[i++], free);
	free(ht->table);
	ft_bzero(ht, sizeof(t_ht));
}

int	ht_insert(t_ht *ht, void *key, void *data)
{
	void	*tmp;
	int		bucket;

	tmp = (void *)key;
	if (!ht_lookup(ht, tmp, NULL))
		return (1);
	bucket = ht->h(key) % ht->buckets;
	lstadd_back(&ht->table[bucket], lstnew(ft_strdup(key), ft_strdup(data)));
	printf("Added Node Address = %p\n", (ht->table[bucket])->next);
	return (0);
}

int	ht_remove(t_ht *ht, void *key)
{
	int		bucket;
	t_lst	*f_node;
	t_lst	*s_node;

	bucket = ht->h(key) % ht->buckets;
	f_node = ht->table[bucket];
	s_node = f_node->next;
	while (s_node != NULL)
	{
		if (!ft_strncmp(s_node->key, key, ft_strlen(key)))
		{
			f_node->next = s_node->next;
			lstdelone(s_node, free);
			return (0);
		}
		f_node = s_node;
		s_node = s_node->next;
	}
	return (1);
}

int	ht_lookup(t_ht *ht, void *key, void **value)
{
	int		bucket;
	t_lst	*node;

	bucket = ht->h(key) % ht->buckets;
	node = ht->table[bucket];
	while (node->next != NULL)
	{
		node = node->next;
		printf("Node Address = %p\n", node);
		if (!ft_strncmp(node->key, key, ft_strlen(key)))
		{
			if (value != NULL)
				*value = ft_strdup(node->data);
			return (0);
		}
	}
	return (1);
}
