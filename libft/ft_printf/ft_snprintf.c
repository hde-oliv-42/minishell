/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 11:46:28 by psergio-          #+#    #+#             */
/*   Updated: 2021/08/02 11:46:28 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_vsnprintf(char *buf, size_t n, const char *format, va_list ap)
{
	t_output	*output;
	int			size;

	output = generate_output((char *)format, ap);
	if (output == NULL)
		return (-1);
	if (output->size < 0)
	{
		free(output->str);
		free(output);
		return (-1);
	}
	size = ft_min(output->size, n);
	ft_memmove(buf, output->str, size);
	buf[size] = '\0';
	free(output);
	return (size);
}

int	ft_snprintf(char *buf, size_t n, const char *format, ...)
{
	int		size;
	va_list	ap;

	va_start(ap, format);
	size = ft_vsnprintf(buf, n, format, ap);
	va_end(ap);
	return (size);
}
