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

void	handle_hex_upper(t_param *param, va_list ap)
{
	handle_hex(param, ap);
	param->specifier = 'X';
	ft_strtoupper(param->str);
}
