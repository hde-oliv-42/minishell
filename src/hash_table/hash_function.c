/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:56:52 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/05 17:41:36 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

unsigned int	hash_function(void *key)
{
	const char		*ptr;
	unsigned int	val;
	unsigned int	tmp;

	val = 0;
	ptr = key;
	while (*ptr != '\0')
	{
		val = (val << 4) + (*ptr);
		tmp = val & 0xf0000000;
		if (tmp)
		{
			val = val ^ (tmp >> 24);
			val = val ^ tmp;
		}
		ptr++;
	}
	return (val % TABLESIZE);
}
