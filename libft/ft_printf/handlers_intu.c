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

static int	handle_zero(t_param *param)
{
	if (param->str[0] == '0')
	{
		free(param->str);
		param->str = ft_strdup("");
		param->str_len = 0;
	}
	return (param->precision);
}

static int	fill_precision(t_param *param)
{
	int		i;
	int		str_len;
	char	*new_str;

	if (param->precision == 0)
		return (handle_zero(param));
	str_len = ft_strlen(param->str);
	if (str_len >= param->precision)
		return (str_len);
	new_str = malloc(param->precision + 1);
	if (new_str == NULL)
		return (-1);
	i = 0;
	new_str[param->precision] = '\0';
	while (i < param->precision - str_len)
		new_str[i++] = '0';
	new_str[i] = '\0';
	ft_strlcat(new_str, param->str, param->precision + 1);
	free(param->str);
	param->str = new_str;
	param->str_len = param->precision;
	return (param->precision);
}

int	print_intu(t_param *param)
{
	if (param->has_precision)
		fill_precision(param);
	if (param->width > param->str_len)
		if (fill_int_width(param) < 0)
			return (-1);
	return (param->str_len);
}

void	handle_intu(t_param *param, va_list ap)
{
	param->specifier = 'u';
	if (param->has_precision)
		param->zero = 0;
	param->str = ft_uitoa(va_arg(ap, int));
	param->str_len = ft_strlen(param->str);
	print_intu(param);
}
