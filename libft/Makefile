SRC		:=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
			ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
			ft_isdigit.c ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lst_do_nothing.c \
			ft_lstmap.c ft_isspace.c ft_intlen.c ft_range.c \
			ft_atoll.c get_next_line.c ft_stox.c ft_uitoa.c ft_stoa_base.c \
			ft_strtoupper.c ft_itox.c ft_memjoin.c ft_dfree.c

PRINTF_SRC := ft_printf/core.c \
	ft_printf/ft_asprintf.c \
	ft_printf/ft_dprintf.c \
	ft_printf/ft_printf.c \
	ft_printf/ft_snprintf.c \
	ft_printf/ft_sprintf.c \
	ft_printf/handlers_binary.c \
	ft_printf/handlers_char.c \
	ft_printf/handlers_hex.c \
	ft_printf/handlers_hex_upper.c \
	ft_printf/handlers_intd.c \
	ft_printf/handlers_inti.c \
	ft_printf/handlers_intu.c \
	ft_printf/handlers_percentage.c \
	ft_printf/handlers_pointer.c \
	ft_printf/handlers_string.c \
	ft_printf/int_utils.c \
	ft_printf/output.c \
	ft_printf/parsers.c \
	ft_printf/specifiers.c

OBJS    :=	$(SRC:.c=.o) $(PRINTF_SRC:.c=.o)

NAME	:=	libft.a
RLIB    :=	ranlib
CC		:=	gcc
LIB		:=	ar rcs

CFLAGS	+=	-Wall -Wextra -Werror
RM		:=	rm -rf



all:		$(NAME)

.c.o:
			$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME):	$(OBJS)
			$(LIB) $(NAME) $(OBJS)
			$(RLIB) $(NAME)

clean:
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re
