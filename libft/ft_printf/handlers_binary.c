/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:53:02 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/14 23:53:02 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	handle_binary(t_param *param, va_list ap)
{
	size_t	nbr;

	param->specifier = 'b';
	if (param->has_precision)
		param->zero = 0;
	nbr = va_arg(ap, size_t);
	if (nbr == 0)
		param->hash = 0;
	param->str = ft_stoa_base(nbr, "01");
	param->str_len = ft_strlen(param->str);
	handle_flags_int(param);
}
