#include "builtins.h"
#include "ft_printf/libftprintf.h"

int	ms_exit(t_program *program)
{
	int	i;
	int	j;

	i = ft_lstsize(program->params);
	ft_dprintf(2, "exit\n");
	j = ft_atoi(((t_string *)program->params->content)->value);
	if (i == 0)
		exit(0);
	else if (i == 1)
		exit(j);
	else
		ft_dprintf(2, "minishell: exit: too many arguments\n");
	return (1);
}
