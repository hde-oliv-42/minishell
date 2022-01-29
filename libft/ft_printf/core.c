/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 08:08:52 by psergio-          #+#    #+#             */
/*   Updated: 2021/08/02 08:08:52 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	join_param(t_output *output, char **format, va_list ap)
{
	t_param	*param;
	char	*tmp;
	int		offset;
	char	*placeholder;

	placeholder = *format;
	param = get_data(placeholder + 1, ap);
	if (param == NULL)
		return (-1);
	if (param->error)
	{
		free(param->str);
		free(param);
		output->size = -1;
		return (-1);
	}
	tmp = ft_memjoin(output->str, output->size, param->str, param->str_len + 1);
	free(output->str);
	output->str = tmp;
	output->size += param->str_len;
	free(param->str);
	offset = param->placeholder_len + 1;
	*format = *format + offset;
	free(param);
	return (offset);
}

/* Joins the current formated string with the next element in the argumnent
 * list. */

int	append_text(t_output *output, char **format)
{
	char	*tmp_str;
	char	*sub_str;
	int		size;
	char	*text;

	text = *format;
	tmp_str = ft_strchr(text, '%');
	if (tmp_str)
		size = tmp_str - text;
	else
		size = ft_strlen(text);
	sub_str = ft_substr(text, 0, size);
	*format = tmp_str;
	tmp_str = output->str;
	output->str = ft_memjoin(output->str, output->size, sub_str, size + 1);
	output->size += size;
	free(tmp_str);
	free(sub_str);
	return (0);
}

t_output	*generate_output(char *format, va_list ap)
{
	t_output	*output;

	output = malloc(sizeof(t_output));
	if (output == NULL)
		return (NULL);
	output->size = 0;
	output->str = ft_calloc(1, 1);
	while (1)
	{
		append_text(output, &format);
		if (format == NULL)
			break ;
		join_param(output, &format, ap);
		if (format == NULL)
			break ;
	}
	return (output);
}
