/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:27:19 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/06 20:53:13 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	export(t_ht *ms_env, char *str)
{
	char	**key_and_value;
	int		rtn;

	if (!str)
	{
		env(ms_env);
		return (0);
	}
	key_and_value = ft_split(str, '=');
	rtn = ht_insert(ms_env, key_and_value[0], key_and_value[1]);
	ft_dfree(key_and_value, 2);
	return (rtn);
}
