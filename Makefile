NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDE = -I src -I $(LIBFT_DIR)
HEADERS = builtins.h parsing.h

RM = rm -rf
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g $(INCLUDE)
LFLAGS = -lreadline -L $(LIBFT_DIR) -lft

vpath %.c src 						\
	src/builtins 					\
	src/process 					\
	src/parsing 					\
	src/tokenizer 					\
	src/prompt 						\
	src/signals 					\
	src/execute 					\
	src/debug

TEST_SRC = pwd.c 					\
		   process.c				\
		   parse.c					\
		   subshell.c				\
		   destroy.c				\
		   redirection.c			\
		   tokenize.c				\
		   tokenize_word.c			\
		   character_checkers.c		\
		   character_checkers2.c	\
		   token_checkers.c			\
		   getters.c				\
		   validator.c				\
		   validator2.c				\
		   destroy_tokens.c			\
		   print_things.c			\
		   prompt.c					\
		   signal_handlers.c		\
		   execute.c				\

SRC = main.c $(TEST_SRC)

TEST_FILES = ./tests/buitins/pwd.test.c 

OBJ_DIR = obj

OBJ =      $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
TEST_OBJ = $(addprefix $(OBJ_DIR)/, $(TEST_SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(NAME)
	./$(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	echo $(SRC)
	echo $(OBJ)
	make -C $(LIBFT_DIR) fclean

re: fclean all

test: $(OBJ_DIR) $(TEST_OBJ)
	gcc $(TEST_OBJ) $(TEST_FILES) ./tests/munit/munit.c -o test $(LFLAGS)
	./test

.PHONY: test
