/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:53:10 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/06 20:56:22 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env(t_ht *ms_env)
{
	int		i;
	t_lst	*tmp;

	i = -1;
	while (++i < ms_env->buckets)
	{	
		if (!(ms_env->table[i])->next)
			continue ;
		tmp = (ms_env->table[i])->next;
		printf("%s=%s\n", tmp->key, tmp->data);
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
			printf("%s=%s\n", tmp->key, tmp->data);
		}
	}
}
