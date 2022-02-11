#include "expand/expand.h"

t_piece	*new_piece(char *value, int len)
{
	t_piece	*piece;

	if (value == NULL)
		return (NULL);
	piece = malloc(sizeof(t_piece));
	if (piece == NULL)
		return (NULL);
	piece->value = value;
	piece->len = len;
	return (piece);
}

int	get_piece(t_list **piece_list, const char *str, int size)
{
	t_piece	*piece;
	char	*value;

	value = ft_substr(str, 0, size);
	if (value == NULL)
		return (0);
	piece = new_piece(value, size);
	if (piece == NULL)
		return (0);
	ft_lstadd_back(piece_list, ft_lstnew(piece));
	return (1);
}

char	*merge_pieces(t_list *piece_list)
{
	t_list	*tmp;
	int		total_len;
	char	*str;

	tmp = piece_list;
	total_len = 0;
	while (tmp)
	{
		total_len += ((t_piece *)tmp->content)->len;
		tmp = tmp->next;
	}
	str = ft_calloc(total_len + 1, 1);
	if (str == NULL)
		return (NULL);
	tmp = piece_list;
	while (tmp)
	{
		ft_strlcat(str, ((t_piece *)tmp->content)->value, total_len + 1);
		tmp = tmp->next;
	}
	return (str);
}

void	destroy_piece(void *piece)
{
	free(((t_piece *)piece)->value);
	free(piece);
}
