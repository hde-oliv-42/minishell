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

static char	*get_last_three_dirs(void)
{
	int			i;
	int			slashs;
	char		*str;
	char		*cwd;
	static char	*previous_dir;

	slashs = 0;
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		free(previous_dir);
		previous_dir = cwd;
	}
	else
		cwd = previous_dir;
	i = ft_strlen(cwd);
	while (slashs < 3 && i > 0)
		if (cwd[i--] == '/')
			slashs++;
	if (i > 0)
		i++;
	str = ft_substr(cwd, i, ft_strlen(cwd) - i);
	return (str);
}

char	*generate_prompt(void)
{
	char	*directory;
	int		result;
	char	*prompt;
	char	*user;

	directory = get_last_three_dirs();
	user = getenv("USER");
	result = ft_asprintf(&prompt, YELLOW "%s" BOLD BLUE " %s"
			GREEN " >>> " RESET, user, directory);
	if (result == -1)
		return (ft_strdup("[error generating prompt] > "));
	free(directory);
	return (prompt);
}
