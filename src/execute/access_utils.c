#include "execute.h"

int	create_path_array(char *path_string, char ***path_array)
{
	char	*str;

	str = ft_substr(path_string, 5, ft_strlen(path_string) - 5);
	*path_array = ft_split(str, ':');
	free(str);
	if (*path_array == NULL)
		return (1);
	return (0);
}

void	free_path_array(char **path_array)
{
	int	i;

	i = 0;
	while (path_array[i])
	{
		free(path_array[i]);
		i++;
	}
	free(path_array);
}

void	fetch_path_string(char **ms_env, char **path_string)
{
	int		i;

	i = 0;
	while (ms_env[i])
	{
		if (!ft_strncmp(ms_env[i], "PATH=", 5))
		{
			*path_string = ms_env[i];
			break ;
		}
		i++;
	}
}

static int	is_relative(char *name)
{
	if (!access(name, F_OK))
		return (1);
	return (0);
}

char	*loop_path_array(char *name, char **path_array)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (path_array[i])
	{
		tmp = ft_strjoin(path_array[i++], "/");
		tmp2 = ft_strjoin(tmp, name);
		free(tmp);
		if (!access(tmp2, F_OK))
		{
			free_path_array(path_array);
			return (tmp2);
		}
		free(tmp2);
	}
	free_path_array(path_array);
	if (is_relative(name))
		return (ft_strdup(name));
	return (NULL);
}
