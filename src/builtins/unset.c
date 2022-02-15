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

// NOTE: If this fails, run to the hills
static int	recreate_env(char ***ms_env, char *dummy)
{
	int		i;
	int		j;
	char	**tmp_env;

	i = 0;
	while ((*ms_env)[i++])
	{
	}
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

static void	find_and_delete(t_list *params, char **ms_env, char *dummy)
{
	int i;

	while (params)
	{
		i = 0;
		while (ms_env[i])
		{
			if (!ft_strncmp(ms_env[i], params->content, ft_strlen(params->content)))
			{
				free(ms_env[i]);
				ms_env[i] = dummy;
			}
			i++;
		}
		params = params->next;
	}
}

// TODO: Do not touch the original ms_env if any malloc fails
int	unset(t_program *program, char ***ms_env)
{
	int		i;
	char	dummy;

	i = ft_lstsize(program->params);
	if (i == 0)
		return (0); // TODO: Check return values with original
	while (program->params)
	{
		find_and_delete(program->params, *ms_env, &dummy);
		program->params = program->params->next;
	}
	return (recreate_env(ms_env, &dummy));
}

