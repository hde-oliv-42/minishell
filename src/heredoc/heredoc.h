/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:26:31 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/18 14:55:55 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "execute/execute.h"
# include "parsing/parsing.h"

char	*get_heredoc(char *delimiter);
void	collect_heredocs(t_program *programs, t_data *data);
int		wait_process(void);

#endif /* !HEREDOC_H */
