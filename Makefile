NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDE = -I src -I $(LIBFT_DIR)
HEADERS = builtins.h parsing.h

RM = rm -rf
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDE)
LFLAGS = -lreadline -L $(LIBFT_DIR) -lft

vpath %.c src 						\
	src/builtins 					\
	src/parsing 					\
	src/tokenizer 					\
	src/heredoc 					\
	src/prompt 						\
	src/signals 					\
	src/execute						\
	src/expand						\
	src/debug

TEST_SRC = 	pwd.c
TEST_SRC += cd.c
TEST_SRC += echo.c
TEST_SRC += unset.c
TEST_SRC += export.c
TEST_SRC += env.c
TEST_SRC += ms_exit.c
TEST_SRC += builtin_utils.c
TEST_SRC += parse.c
TEST_SRC += subshell.c
TEST_SRC += destroy.c
TEST_SRC += redirection.c
TEST_SRC += tokenize.c
TEST_SRC += tokenize_word.c
TEST_SRC += character_checkers.c
TEST_SRC += character_checkers2.c
TEST_SRC += token_checkers.c
TEST_SRC += getters.c
TEST_SRC += validator.c
TEST_SRC += validator2.c
TEST_SRC += destroy_tokens.c
TEST_SRC += execute.c
TEST_SRC += execute_subshell.c
TEST_SRC += execute_utils.c
TEST_SRC += execute_builtin.c
TEST_SRC += child_utils.c
TEST_SRC += parent_utils.c
TEST_SRC += access_methods.c
TEST_SRC += access_utils.c
TEST_SRC += ms_env.c
TEST_SRC += print_things.c
TEST_SRC += prompt.c
TEST_SRC += signal_handlers.c
TEST_SRC += signal_ignorers.c
TEST_SRC += heredoc_signals.c
TEST_SRC += expand.c
TEST_SRC += pieces.c
TEST_SRC += expand_tokens.c
TEST_SRC += expand_asterisk.c
TEST_SRC += heredoc.c
TEST_SRC += heredoc_subprocess.c

SRC = main.c $(TEST_SRC)

TEST_FILES = ./tests/buitins/pwd.test.c 

OBJ_DIR = obj

OBJ =      $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
TEST_OBJ = $(addprefix $(OBJ_DIR)/, $(TEST_SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

$(LIBFT):
	make -j6 -C $(LIBFT_DIR)

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
