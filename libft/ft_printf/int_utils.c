/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 19:42:26 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/14 19:42:26 by psergio-         ###   ########.fr       */
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

int	fill_precision(t_param *param)
{
	int		i;
	int		str_len;
	char	*new_str;
	int		is_neg;

	if (param->precision == 0)
		return (handle_zero(param));
	is_neg = param->str[0] == '-';
	str_len = ft_strlen(param->str);
	if (str_len >= param->precision + is_neg)
		return (str_len);
	new_str = malloc(param->precision + is_neg + 1);
	if (new_str == NULL)
		return (-1);
	i = 0;
	if (is_neg)
		new_str[i] = '-';
	while (i < param->precision - str_len + is_neg)
		new_str[i++ + is_neg] = '0';
	new_str[i + is_neg] = '\0';
	ft_strlcat(new_str, param->str + is_neg, param->precision + 1 + is_neg);
	free(param->str);
	param->str = new_str;
	param->str_len = param->precision + is_neg;
	return (param->precision);
}

int	fill_int_width(t_param *param)
{
	size_t	i;
	char	*new_str;
	int		prefix;
	int		has_prefix;

	if (param->minus || !param->zero)
		return (fill_width(param));
	new_str = malloc(param->width + 1);
	if (new_str == NULL)
		return (-1);
	has_prefix = !ft_isdigit(param->str[0]);
	prefix = param->str[0];
	i = 0;
	if (has_prefix)
		new_str[0] = prefix;
	while (i < param->width - param->str_len)
		new_str[i++ + has_prefix] = '0';
	new_str[i + has_prefix] = '\0';
	ft_strlcat(new_str, param->str + has_prefix, param->width + 1);
	free(param->str);
	param->str = new_str;
	param->str_len = param->width;
	return (1);
}

void	prefix_positive(t_param *param)
{
	char	*tmp;

	tmp = param->str;
	if (param->plus)
		param->str = ft_strjoin("+", tmp);
	else if (param->space)
		param->str = ft_strjoin(" ", tmp);
	param->str_len++;
	free(tmp);
}

int	handle_flags_int(t_param *param)
{
	if (param->has_precision)
		if (fill_precision(param) < 0)
			return (-1);
	if ((param->plus || param->space) && param->str[0] != '-')
		prefix_positive(param);
	if (param->width > param->str_len)
		if (fill_int_width(param) < 0)
			return (-1);
	return (param->str_len);
}
