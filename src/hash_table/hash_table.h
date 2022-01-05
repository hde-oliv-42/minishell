/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:57:23 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/05 20:27:53 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H
# define TABLESIZE 11

# include "libft.h"

typedef struct s_lst
{
	void			*data;
	void			*key;
	struct s_lst	*next;
}	t_lst;

typedef struct s_ht
{
	int					buckets;
	unsigned int		(*h)(void *k);
	t_lst				**table;
}	t_ht;

unsigned int	hash_function(void *key);
int				ht_init(t_ht *ht, int buckets, unsigned int (*h)(void *k));
void			ht_destroy(t_ht *ht);
int				ht_insert(t_ht *ht, void *key, void *data);
int				ht_remove(t_ht *ht, void *key);
int				ht_lookup(t_ht *ht, void *key, void **value);
void			lstdelone(t_lst *lst, void (*del)(void *));
void			lstclear(t_lst **lst, void (*del)(void *));
t_lst			*lstlast(t_lst *lst);
void			lstadd_back(t_lst **lst, t_lst *new);
t_lst			*lstnew(void *key, void *data);

#endif
