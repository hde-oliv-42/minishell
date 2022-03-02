NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDE = -I src -I $(LIBFT_DIR)
HEADERS = builtins.h parsing.h

RM = rm -rf
CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3 $(INCLUDE)
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

SRC =  main.c
SRC += pwd.c
SRC += cd.c
SRC += echo.c
SRC += unset.c
SRC += export.c
SRC += env.c
SRC += ms_exit.c
SRC += builtin_utils.c
SRC += parse.c
SRC += string.c
SRC += subshell.c
SRC += destroy.c
SRC += redirection.c
SRC += tokenize.c
SRC += tokenize_word.c
SRC += character_checkers.c
SRC += character_checkers2.c
SRC += token_checkers.c
SRC += getters.c
SRC += validator.c
SRC += validator2.c
SRC += destroy_tokens.c
SRC += execute.c
SRC += execute_subshell.c
SRC += execute_utils.c
SRC += execute_builtin.c
SRC += child_utils.c
SRC += parent_utils.c
SRC += access_methods.c
SRC += access_utils.c
SRC += wait_utils.c
SRC += ms_env.c
SRC += print_things.c
SRC += prompt.c
SRC += signal_handlers.c
SRC += signal_ignorers.c
SRC += heredoc_signals.c
SRC += expand.c
SRC += pieces.c
SRC += expand_tokens.c
SRC += expand_asterisk.c
SRC += expand_env_variables.c
SRC += heredoc.c
SRC += heredoc_subprocess.c

TEST_FILES = ./tests/buitins/pwd.test.c 

OBJ_DIR = obj

OBJ =      $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

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

.PHONY: test
