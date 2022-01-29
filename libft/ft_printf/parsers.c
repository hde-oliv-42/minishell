/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 20:19:48 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/09 20:19:48 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	is_flag(char c)
{
	return (c == '0' || c == '-' || c == '#' || c == ' ' || c == '+');
}

/**
 * Fetches all the data related to the current param to be printed based on the
 * placeholder.
 * Returns the amount of characters that were related to the param in case of
 * valid flags.
 * */

static int	get_flags(const char *str, t_param *param, va_list ap)
{
	int		chars;

	(void) ap;
	if (!*str)
		return (0);
	chars = 0;
	while (is_flag(str[chars]))
	{
		if (str[chars] == '-')
			param->minus = 1;
		else if (str[chars] == '0')
			param->zero = 1;
		else if (str[chars] == '#')
			param->hash = 1;
		else if (str[chars] == ' ')
			param->space = 1;
		else if (str[chars] == '+')
			param->plus = 1;
		chars++;
	}
	return (chars);
}

static int	get_width(const char *str, t_param *param, va_list ap)
{
	int	width;
	int	offset;

	if (*str == '*')
		width = va_arg(ap, int);
	else
		width = ft_atoi(str);
	if (width < 0)
	{
		width = -width;
		param->minus = 1;
	}
	param->width = width;
	offset = 0;
	if (*str == '*')
		return (1);
	else
		while (ft_isdigit(*str++))
			offset++;
	return (offset);
}

static int	get_precision(const char *str, t_param *param, va_list ap)
{
	int	offset;

	param->has_precision = 0;
	offset = 0;
	if (*str++ == '.')
	{
		offset = 1;
		param->has_precision = 1;
		if (*str == '*')
		{
			param->precision = va_arg(ap, int);
			if (param->precision < 0)
				param->has_precision = 0;
		}
		else
			param->precision = ft_atoi(str);
		if (*str == '*')
			return (2);
		else
			while (ft_isdigit(*str++))
				offset++;
	}
	return (offset);
}

t_param	*get_data(const char *str, va_list ap)
{
	t_param	*param;
	int		offset;

	param = ft_calloc(1, sizeof(t_param));
	if (param == NULL)
		return (NULL);
	param->error = 0;
	param->specifier = '\0';
	param->placeholder_len = 1;
	offset = get_flags(str, param, ap);
	offset += get_width(str + offset, param, ap);
	offset += get_precision(str + offset, param, ap);
	get_str(str[offset], param, ap);
	if (param->str == NULL)
		return (param);
	if (param->specifier != 'c')
		param->str_len = ft_strlen(param->str);
	param->placeholder_len += offset;
	return (param);
}
