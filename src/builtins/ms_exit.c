#include "builtins.h"
#include "ft_printf/libftprintf.h"
#include "libft.h"

extern char	**g_env;

static int	is_number(char *number)
{
	int	size;
	int	i;

	size = ft_strlen(number);
	i = 1;
	if (number[0] != '-' && !ft_isdigit(number[0]))
		return (0);
	while (i < size)
	{
		if (!ft_isdigit(number[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ms_exit(t_program *program, t_data *data)
{
	int	i;
	int	j;

	i = ft_lstsize(program->params);
	j = ft_atoi(((t_string *)program->params->content)->value);
	ft_dprintf(2, "exit\n");
	if (!is_number(((t_string *)program->params->content)->value))
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", ((t_string *)program->params->content)->value);
	else if (i == 0)
	{
		destroy_pipeline(data->program_list);
		ft_dfree(g_env);
		exit(0);
	}
	else if (i == 1)
	{
		destroy_pipeline(data->program_list);
		ft_dfree(g_env);
		exit(j);
	}
	else
		ft_dprintf(2, "minishell: exit: too many arguments\n");
	return (1);
}
