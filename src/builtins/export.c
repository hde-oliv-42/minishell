/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:27:19 by hde-oliv          #+#    #+#             */
/*   Updated: 2022/01/06 20:53:13 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	export_error(char *str)
{
	printf("minishell: export: '%s': not a valid identifier\n", str);
	return (1);
}

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
		return (1);
	i = 0;
	while ((*ms_env)[i])
	{
		tmp_env[i] = (*ms_env)[i];
		i++;
	}
	tmp_env[i] = ft_strdup(var_with_content);
	free(*ms_env);
	*ms_env = tmp_env;
	return (0);
}

static int	handle_already_exists(char *var_with_content, char **ms_env)
{
	char	*var;
	int		i;

	var = ft_substr(var_with_content, \
					0, \
					ft_strchr(var_with_content, '=') - var_with_content);
	if (var == NULL)
		return (1);
	i = 0;
	while (ms_env[i])
	{
		if (!ft_strncmp(ms_env[i], var, ft_strlen(var)))
		{
			free(ms_env[i]);
			ms_env[i] = ft_strdup(var_with_content);
			if (ms_env == NULL)
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	var_already_exists(char *var_with_content, char **ms_env)
{
	char	*var;
	int		i;

	var = ft_substr(var_with_content, \
					0, \
					ft_strchr(var_with_content, '=') - var_with_content + 1);
	// TODO: Check later if this is sufficient to handle errors
	if (var == NULL)
		return (-1);
	i = 0;
	while (ms_env[i])
	{
		// TODO: Check later if this will break
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

int	export(t_program *program, char ***ms_env)
{
	char	*equals_ptr;
	t_list	*tmp;

	tmp = program->params;
	if (ft_lstsize(program->params) == 0)
	{
		env(*ms_env);
		return (0);
	}
	while (tmp)
	{
		equals_ptr = ft_strchr(tmp->content, '=');
		if (!equals_ptr)
		{
			tmp = tmp->next;
			continue ;
		}
		if (equals_ptr == tmp->content)
			return (export_error(tmp->content));
		else
		{
			if (var_already_exists(tmp->content, *ms_env) == 1)
				return (handle_already_exists(tmp->content, \
												*ms_env));
			else
				return (handle_new_var(tmp->content, ms_env));
		}
		tmp = tmp->next;
	}
	return (1);
}
