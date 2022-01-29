/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 23:30:59 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/02 23:30:59 by psergio-         ###   ########.fr       */
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

static int	fill_hex_width(t_param *param)
{
	size_t	i;
	char	*new_str;
	int		has_hash;

	if (param->minus || !param->zero)
		return (fill_width(param));
	new_str = malloc(param->width + 1);
	if (new_str == NULL)
		return (-1);
	has_hash = param->hash * 2;
	i = 0;
	if (has_hash)
	{
		new_str[0] = '0';
		new_str[1] = param->specifier;
	}
	while (i < param->width - param->str_len)
		new_str[i++ + has_hash] = '0';
	new_str[i + has_hash] = '\0';
	ft_strlcat(new_str, param->str + has_hash, param->width + 1);
	free(param->str);
	param->str = new_str;
	param->str_len = param->width;
	return (1);
}

static int	handle_flags(t_param *param)
{
	char	*tmp;

	if (param->has_precision)
		fill_precision(param);
	if (param->hash)
	{
		tmp = param->str;
		if (param->specifier == 'X')
			param->str = ft_strjoin("0X", tmp);
		else
			param->str = ft_strjoin("0x", tmp);
		param->str_len += 2;
		free(tmp);
	}
	if (param->width > param->str_len)
		if (fill_hex_width(param) < 0)
			return (-1);
	return (param->str_len);
}

void	handle_hex(t_param *param, va_list ap)
{
	unsigned int	nbr;

	param->specifier = 'x';
	if (param->has_precision)
		param->zero = 0;
	nbr = va_arg(ap, unsigned int);
	if (nbr == 0)
		param->hash = 0;
	param->str = ft_itox(nbr);
	param->str_len = ft_strlen(param->str);
	if (handle_flags(param) == -1)
		param->error = 1;
}
