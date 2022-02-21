/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:17:56 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/21 19:20:17 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structures.h>
#include "tokenizer/tokenizer.h"

t_string	*new_string(t_token *word)
{
	t_string	*string;

	string = ft_calloc(1, sizeof(t_string));
	if (string == NULL)
		return (NULL);
	string->value = ft_strdup(word->value);
	string->should_expand = word->should_expand;
	return (string);
}
