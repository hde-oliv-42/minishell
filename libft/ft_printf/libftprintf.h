/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 20:09:07 by psergio-          #+#    #+#             */
/*   Updated: 2021/06/20 20:09:07 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <libft.h>

struct s_param
{
	int		precision;
	size_t	width;
	char	*str;
	size_t	str_len;
	int		minus;
	int		zero;
	int		hash;
	int		space;
	int		plus;
	size_t	placeholder_len;
	int		has_precision;
	char	specifier;
	int		error;
};

struct s_output {
	int		size;
	char	*str;
};

typedef struct s_output	t_output;
typedef struct s_param	t_param;

t_param		*get_data(const char *str, va_list ap);
t_output	*generate_output(char *format, va_list ap);

void		get_str(char converter, t_param *param, va_list ap);
void		handle_binary(t_param *param, va_list ap);
void		handle_char(t_param *param, va_list ap);
void		handle_string(t_param *param, va_list ap);
void		handle_pointer(t_param *param, va_list ap);
void		handle_intd(t_param *param, va_list ap);
void		handle_inti(t_param *param, va_list ap);
void		handle_intu(t_param *param, va_list ap);
void		handle_hex(t_param *param, va_list ap);
void		handle_hex_upper(t_param *param, va_list ap);
void		handle_percentage(t_param *param);

// formating functions
int			fill_width(t_param *param);
void		prefix_positive(t_param *param);

/**
 * Common functiond that handle flags for integer-like specifiers
 */
int			handle_flags_int(t_param *param);
int			fill_int_width(t_param *param);

int			ft_printf(const char *format, ...);
int			ft_vprintf(const char *format, va_list ap);
int			ft_dprintf(int fd, const char *format, ...);
int			ft_vdprintf(int fd, const char *format, va_list ap);
int			ft_sprintf(char *buf, const char *format, ...);
int			ft_vsprintf(char *buf, const char *format, va_list ap);
int			ft_snprintf(char *buf, size_t n, const char *format, ...);
int			ft_vsnprintf(char *buf, size_t n, const char *format, va_list ap);
int			ft_asprintf(char **str, const char *format, ...);
int			ft_vasprintf(char **str, const char *format, va_list ap);

#endif
