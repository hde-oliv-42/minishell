/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 10:49:55 by psergio-          #+#    #+#             */
/*   Updated: 2021/08/02 10:49:55 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_output	*output;
	int			size;

	output = generate_output((char *)format, ap);
	if (output == NULL)
		return (-1);
	write(fd, output->str, output->size);
	free(output->str);
	size = output->size;
	free(output);
	return (size);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int			chars_printed;
	va_list		ap;

	chars_printed = 0;
	va_start(ap, format);
	chars_printed = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (chars_printed);
}
