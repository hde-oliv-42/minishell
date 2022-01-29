/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_intd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 18:18:07 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/02 18:18:07 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	handle_intd(t_param *param, va_list ap)
{
	param->specifier = 'd';
	if (param->has_precision)
		param->zero = 0;
	param->str = ft_itoa(va_arg(ap, int));
	param->str_len = ft_strlen(param->str);
	if (handle_flags_int(param) == -1)
		param->error = 1;
}
