/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:19:39 by psergio-          #+#    #+#             */
/*   Updated: 2022/01/29 14:25:11 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BOLD	"\001\x1b[1m\002"
#define RED		"\001\x1b[31m\002"
#define GREEN 	"\001\x1b[32m\002"
#define YELLOW	"\001\x1b[33m\002"
#define BLUE	"\001\x1b[34m\002"
#define MAGENTA	"\001\x1b[35m\002"
#define CYAN	"\001\x1b[36m\002"
#define RESET	"\001\x1b[0m\002"


char	*generate_prompt(void)
{
	return (BOLD BLUE "minishell$ " RESET);
}

