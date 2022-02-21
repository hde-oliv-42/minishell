/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:26:24 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/21 19:30:52 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "execute/ms_env.h"

int	skip_dollar(t_list **piece_list, char chr)
{
	char	*delimiters;
	t_piece	*piece;
	char	*value;

	delimiters = "$ =@(*)#";
	value = malloc(3);
	value[0] = '$';
	if (ft_strchr(delimiters, chr))
		value[1] = chr;
	else
		value[1] = '\0';
	value[2] = '\0';
	piece = new_piece(value, ft_strlen(value));
	ft_lstadd_back(piece_list, ft_lstnew(piece));
	return (1);
}

char	*get_last_status(t_data *data)
{
	char	*status_str;

	status_str = ft_itoa(*data->wstatus);
	if (status_str == NULL)
	{
		perror("error getting last status");
		return (NULL);
	}
	return (status_str);
}

int	get_env_variable(
		t_list **piece_list, const char *str, int *size, t_data *data)
{
	char	*delimiters;
	char	*key;
	char	*value;
	t_piece	*piece;

	delimiters = VAR_DELIMITERS;
	(*size)++;
	if (ft_strchr(delimiters, str[*size]))
		return (skip_dollar(piece_list, str[*size]));
	while (!ft_strchr(delimiters, str[*size]))
		(*size)++;
	key = ft_substr(str, 0, *size);
	(*size)--;
	if (str_equals(key, "?"))
		value = get_last_status(data);
	else
		value = search_env(key);
	if (value == NULL)
		value = ft_strdup("");
	free(key);
	piece = new_piece(value, ft_strlen(value));
	ft_lstadd_back(piece_list, ft_lstnew(piece));
	return (1);
}
