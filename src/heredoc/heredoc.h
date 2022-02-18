/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:26:31 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/13 19:26:56 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "parsing/parsing.h"

char	*get_heredoc(char *delimiter);
void	collect_heredocs(t_program *programs);

#endif /* !HEREDOC_H */
