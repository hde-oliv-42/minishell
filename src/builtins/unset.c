/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:56:33 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/06 20:58:55 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

static int	recreate_env(char ***ms_env, char *dummy)
{
	int		i;
	int		j;
	char	**tmp_env;

	i = ms_env_size(*ms_env);
	tmp_env = (char **) ft_calloc(i + 1, sizeof(char *));
	if (tmp_env == NULL)
		return (1);
	i = 0;
	j = 0;
	while ((*ms_env)[i])
	{
		if ((*ms_env)[i] == dummy)
		{
			i++;
			continue ;
		}
		tmp_env[j] = (*ms_env)[i];
		i++;
		j++;
	}
	free(*ms_env);
	*ms_env = tmp_env;
	return (0);
}

static void	find_and_delete(t_list *params, char ***ms_env, char *dummy)
{
	int	i;

	while (params)
	{
		i = 0;
		while ((*ms_env)[i])
		{
			if (!ft_strncmp((*ms_env)[i], \
							((t_string *)params->content)->value, \
							ft_strlen(((t_string *)params->content)->value)))
			{
				free((*ms_env)[i]);
				(*ms_env)[i] = dummy;
			}
			i++;
		}
		params = params->next;
	}
}

int	unset(t_program *program, char ***ms_env)
{
	int		i;
	char	dummy;
	char	**tmp;
	t_list	*params;

	params = program->params;
	i = ft_lstsize(params);
	if (i == 0)
		return (0);
	if (duplicate_env(*ms_env, &tmp))
		return (1);
	while (params)
	{
		find_and_delete(params, &tmp, &dummy);
		params = params->next;
	}
	if (recreate_env(&tmp, &dummy))
		return (1);
	ft_dfree(*ms_env);
	*ms_env = tmp;
	return (0);
}
