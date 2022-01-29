/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 11:06:56 by psergio-          #+#    #+#             */
/*   Updated: 2021/08/02 11:06:56 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_vsprintf(char *buf, const char *format, va_list ap)
{
	t_output	*output;
	int			size;

	output = generate_output((char *)format, ap);
	if (output == NULL)
		return (-1);
	ft_memmove(buf, output->str, output->size);
	size = output->size;
	buf[output->size] = '\0';
	free(output);
	return (size);
}

int	ft_sprintf(char *buf, const char *format, ...)
{
	int		chars_printed;
	va_list	ap;

	va_start(ap, format);
	chars_printed = ft_vsprintf(buf, format, ap);
	va_end(ap);
	return (chars_printed);
}
