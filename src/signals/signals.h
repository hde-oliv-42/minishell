/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:13:15 by psergio-          #+#    #+#             */
/*   Updated: 2022/02/19 15:32:51 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <structures.h>
# include <sys/wait.h>

void	reset_child_signals(void);
void	reset_signals(void);
void	handle_signals(void);
void	ignore_signals(void);
void	set_heredoc_signals(t_data *data, t_list **string_list);

#endif
