/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 11:28:02 by psergio-          #+#    #+#             */
/*   Updated: 2021/08/27 11:28:02 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_vasprintf(char **str, const char *format, va_list ap)
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
	size = output->size;
	*str = output->str;
	free(output);
	return (size);
}

int	ft_asprintf(char **str, const char *format, ...)
{
	int		size;
	va_list	ap;

	va_start(ap, format);
	size = ft_vasprintf(str, format, ap);
	va_end(ap);
	return (size);
}
