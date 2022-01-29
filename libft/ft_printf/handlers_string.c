/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 22:36:21 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/02 22:36:21 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	handle_flags(t_param *param)
{
	if (param->str_len < param->width)
		if (fill_width(param) < 0)
			return (-1);
	return (param->str_len);
}

void	handle_string(t_param *param, va_list ap)
{
	char	*str_param;

	param->specifier = 's';
	str_param = va_arg(ap, char *);
	if (str_param == NULL)
		str_param = "(null)";
	if (param->has_precision)
		param->str = ft_substr(str_param, 0, param->precision);
	else
		param->str = ft_strdup(str_param);
	param->str_len = ft_strlen(param->str);
	handle_flags(param);
}
