/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifiers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 20:26:54 by psergio-          #+#    #+#             */
/*   Updated: 2021/06/26 20:26:54 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

void	get_str(char converter, t_param *param, va_list ap)
{
	if (converter == 'b')
		handle_binary(param, ap);
	else if (converter == 'c')
		handle_char(param, ap);
	else if (converter == 's')
		handle_string(param, ap);
	else if (converter == 'p')
		handle_pointer(param, ap);
	else if (converter == 'd')
		handle_intd(param, ap);
	else if (converter == 'i')
		handle_inti(param, ap);
	else if (converter == 'u')
		handle_intu(param, ap);
	else if (converter == 'x')
		handle_hex(param, ap);
	else if (converter == 'X')
		handle_hex_upper(param, ap);
	else if (converter == '%')
		handle_percentage(param);
	else
		param->str = NULL;
}
