/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 22:57:31 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/02 22:57:31 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*int_to_pointer(size_t nbr)
{
	char	*hex;
	char	*address;

	if (nbr == 0)
	{
		address = ft_strdup("0x0");
	}
	else
	{
		hex = ft_stox(nbr);
		address = ft_strjoin("0x", hex);
		free(hex);
	}
	return (address);
}

static int	handle_flags(t_param *param)
{
	if (param->str_len < param->width)
		if (fill_width(param) < 0)
			return (-1);
	return (param->str_len);
}

void	handle_pointer(t_param *param, va_list ap)
{
	param->specifier = 'p';
	param->str = int_to_pointer(va_arg(ap, size_t));
	param->str_len = ft_strlen(param->str);
	if (handle_flags(param) == -1)
		param->error = 1;
}
