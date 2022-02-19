#ifndef DEBUG
# define DEBUG

#include <libft.h>
#include <parsing/parsing.h>
#include <errno.h>
#include <wait.h>

void	print_tokens(t_token **tokens);
void	print_pipeline(t_program *program);
void	print_array(char **array);
void	print_linked_list(t_list *list);

#endif /* !DEBUG */
