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

#include "execute/execute.h"
#include "ft_printf/libftprintf.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#define BOLD	"\001\x1b[1m\002"
#define RED		"\001\x1b[31m\002"
#define GREEN 	"\001\x1b[32m\002"
#define YELLOW	"\001\x1b[33m\002"
#define BLUE	"\001\x1b[34m\002"
#define MAGENTA	"\001\x1b[35m\002"
#define CYAN	"\001\x1b[36m\002"
#define RESET	"\001\x1b[0m\002"

static char	*get_last_three_dirs(t_data *data)
{
	int			i;
	int			slashs;
	char		*str;
	char		*cwd;

	slashs = 0;
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		free(data->cwd);
		data->cwd = cwd;
	}
	else
		cwd = data->cwd;
	i = ft_strlen(cwd);
	while (slashs < 3 && i > 0)
		if (cwd[--i] == '/')
			slashs++;
	if (i > 0)
		i++;
	str = ft_substr(cwd, i, ft_strlen(cwd) - i);
	return (str);
}

static char	*format_prompt(char *user, char *directory, t_data *data)
{
	int		result;
	char	*arrow_color;
	char	*padding;
	char	*prompt;

	arrow_color = GREEN;
	padding = "";
	if (data->wstatus)
	{
		arrow_color = RED;
		padding = " ";
	}
	result = ft_asprintf(&prompt,
			YELLOW "%s" BOLD BLUE " %s" RED " %.d" "%s%s>>> " RESET,
			user, directory, data->wstatus, padding, arrow_color);
	if (result == -1)
		return (ft_strdup("[error generating prompt] > "));
	return (prompt);
}

char	*generate_prompt(t_data *data)
{
	char	*directory;
	char	*prompt;
	char	*user;

	directory = get_last_three_dirs(data);
	user = getenv("USER");
	prompt = format_prompt(user, directory, data);
	free(directory);
	return (prompt);
}
