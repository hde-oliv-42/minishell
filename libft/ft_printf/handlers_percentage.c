/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_percentage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 23:40:40 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/02 23:40:40 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	print_percent(t_param *param)
{
	size_t	i;

	if (param->width > param->str_len)
		if (fill_width(param) < 0)
			return (-1);
	if (param->zero)
	{
		i = 0;
		while (i < param->str_len)
		{
			if (param->str[i] == ' ')
				param->str[i] = '0';
			if (param->str[i] == '%')
				break ;
			i++;
		}
	}
	write(1, param->str, param->str_len);
	return (param->str_len);
}

void	handle_percentage(t_param *param)
{
	param->specifier = '%';
	param->str = ft_strdup("%");
}
