NAME = minishell

RM = rm -rf
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LFLAGS = -lreadline

INCLUDE = include

vpath %.c src

SRC = main.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(LFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

