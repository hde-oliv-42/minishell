/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 22:52:39 by psergio-          #+#    #+#             */
/*   Updated: 2021/07/02 22:52:39 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*char_to_str(int c)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = (char)c;
	return (str);
}

static int	fill_char_width(t_param *param)
{
	char	*new_str;
	size_t	i;

	new_str = malloc(param->width + 1);
	if (new_str == NULL)
		return (-1);
	i = 0;
	if (!param->minus)
		while (i < param->width - 1)
			new_str[i++] = ' ';
	new_str[i] = param->str[0];
	if (param->minus)
	{
		while (++i < param->width)
			new_str[i] = ' ';
		new_str[i] = '\0';
	}
	free(param->str);
	param->str = new_str;
	param->str_len = param->width;
	return (1);
}

static int	handle_flags(t_param *param)
{
	param->str_len = 1;
	if (param->width > 1)
		if (fill_char_width(param) < 0)
			return (-1);
	return (param->str_len);
}

void	handle_char(t_param *param, va_list ap)
{
	param->specifier = 'c';
	param->str = char_to_str(va_arg(ap, int));
	if (handle_flags(param) == -1)
		param->error = 1;
}
