/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:27:19 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:19 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

#define ERRID "minishell: export: '%s': not a valid identifier\n"
#define ERRMA "minishell: export:%s could not allocate memory\n"

static int	handle_new_var(char *var_with_content, char ***ms_env)
{
	int		i;
	char	**tmp_env;

	i = 0;
	while ((*ms_env)[i++])
	{
	}
	tmp_env = (char **) ft_calloc(i + 2, sizeof(char *));
	if (tmp_env == NULL)
		return (-1);
	i = 0;
	while ((*ms_env)[i])
	{
		tmp_env[i] = (*ms_env)[i];
		i++;
	}
	tmp_env[i] = ft_strdup(var_with_content);
	if (tmp_env[i] == NULL)
		return (-1);
	free(*ms_env);
	*ms_env = tmp_env;
	return (0);
}

static int	handle_exists(char *varc, char **ms_env)
{
	char	*var;
	int		i;

	var = ft_substr(varc, 0, ft_strchr(varc, '=') - varc + 1);
	if (var == NULL)
		return (-1);
	i = 0;
	while (ms_env[i])
	{
		if (!ft_strncmp(ms_env[i], var, ft_strlen(var)))
		{
			free(ms_env[i]);
			free(var);
			ms_env[i] = ft_strdup(varc);
			if (ms_env == NULL)
				return (-1);
			return (0);
		}
		i++;
	}
	free(var);
	return (1);
}

static int	var_exists(char *varc, char **ms_env)
{
	char	*var;
	int		i;

	var = ft_substr(varc, 0, ft_strchr(varc, '=') - varc + 1);
	if (var == NULL)
		return (-1);
	i = 0;
	while (ms_env[i])
	{
		if (!ft_strncmp(ms_env[i], var, ft_strlen(var)))
		{
			free(var);
			return (1);
		}
		i++;
	}
	free(var);
	return (0);
}

void	check_export_error(t_list *tmp, char *equals_ptr)
{
	if (equals_ptr == ((t_string *)tmp->content)->value)
		export_error(((t_string *)tmp->content)->value, ERRID);
}

int	export(t_program *program, char ***ms_env)
{
	char	*equals_ptr;
	char	**tmp_env;
	t_list	*tmp;
	int		i;

	tmp = program->params;
	duplicate_env(*ms_env, &tmp_env);
	if (ft_lstsize(tmp) == 0)
		return (env(*ms_env));
	i = 0;
	while (tmp && !i)
	{
		equals_ptr = ft_strchr(((t_string *)tmp->content)->value, '=');
		check_export_error(tmp, equals_ptr);
		if (equals_ptr)
		{
			i = var_exists(((t_string *)tmp->content)->value, tmp_env);
			if (i == 1)
				i = handle_exists(((t_string *)tmp->content)->value, tmp_env);
			else if (i == 0)
				i = handle_new_var(((t_string *)tmp->content)->value, &tmp_env);
		}
		tmp = tmp->next;
	}
	return (swap_env(ms_env, tmp_env, i));
}
