/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:30:20 by hde-oliv          #+#    #+#             */
/*   Updated: 2021/11/09 21:41:40 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	has_format_tag(char *string)
{
	if (ft_strchr(string, '%'))
		return (1);
	return (0);
}

int	send_output(char *string)
{
	return (write(1, string, ft_strlen(string)));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		tmp_count;
	char	*tmp_format;

	if (!has_format_tag((char *)format))
		return (send_output((char *)format));
	va_start(args, format);
	tmp_format = (char *)format;
	count = tag_handler(&tmp_format, args);
	tmp_count = 1;
	while (*tmp_format && tmp_count != -1)
	{
		tmp_count = tag_handler(&tmp_format, args);
		count += tmp_count;
	}
	va_end(args);
	if (tmp_count == -1)
		return (tmp_count);
	return (count);
}
