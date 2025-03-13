NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

# Couleurs pour les messages
GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
BLUE = \033[38;2;15;101;214m
RESET = \033[0m

LIBFT_DIR = mandatory/includes/libft/
LIBFT_FILE = libft.a
GNL_DIR = mandatory/includes/gnl
GNL_FILE = gnl.a

OBJ_PATH = obj/
SRC_PATH = mandatory/src/
UTILS_PATH = mandatory/utils/
BUILTIN_PATH = mandatory/builtins/
EXECUTION_PATH= mandatory/execution/
PARSING_PATH = mandatory/parsing/
HEREDOC_PATH= mandatory/heredoc/
SIGNALS_PATH = mandatory/signals/

SRC = main.c create_env.c delete_env.c prompt.c
EXECUTION = execution.c init.c open.c pid_manager.c builtins.c command_preparation.c fd_manager.c
UTIL = commands.c sort_list.c env_replacer.c transform_env.c utils.c parsing_utils.c \
	   split_skip_quotes_utils.c split_utils.c dollars_utils.c cpy_txt_utils.c quotes_parser.c ft_realloc.c error_handle.c execution_utils.c
BUILTIN = pwd.c cd.c echo.c export.c unset.c env.c exit.c
HEREDOC = heredoc.c heredoc_expand.c
PARSING = parsing.c text_handle.c clean_commands.c flags_handle.c dollars.c quote_parsing.c ambigous.c triple.c
SIGNAL = heredoc_signals.c signals.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))
UTILS = $(addprefix $(SRC_PATH), $(UTIL))
BUILTINS = $(addprefix $(BUILTIN_PATH), $(BUILTIN))
PARSINGS = $(addprefix $(PARSING_PATH), $(PARSING))
HEREDOCS = $(addprefix $(HEREDOC_PATH), $(HEREDOC))
SIGNALS = $(addprefix $(SRC_PATH), $(SIGNAL))
EXECUTIONS = $(addprefix $(EXECUTION_PATH), $(EXECUTION))


OBJ_SRC = $(SRC:.c=.o)
OBJ_UTILS = $(UTIL:.c=.o)
OBJ_BUILTIN = $(BUILTIN:.c=.o)
OBJ_EXECUTION = $(EXECUTION:.c=.o)
OBJ_PARSING = $(PARSING:.c=.o)
OBJ_HEREDOC = $(HEREDOC:.c=.o)
OBJ_SIGNALS = $(SIGNAL:.c=.o)

OBJS_SRC = $(addprefix $(OBJ_PATH), $(OBJ_SRC))
LIBFT_LIB = $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))
OBJS_UTILS = $(addprefix $(OBJ_PATH), $(OBJ_UTILS))
OBJS_BUILTIN = $(addprefix $(OBJ_PATH), $(OBJ_BUILTIN))
OBJS_PARSING = $(addprefix $(OBJ_PATH), $(OBJ_PARSING))
OBJS_HEREDOC = $(addprefix $(OBJ_PATH), $(OBJ_HEREDOC))
OBJS_SIGNALS = $(addprefix $(OBJ_PATH), $(OBJ_SIGNALS))
OBJS_EXECUTIONS = $(addprefix $(OBJ_PATH), $(OBJ_EXECUTION))


LIBFT_LIB = $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))

all: $(NAME)
	@:	

$(NAME): $(LIBFT_LIB) $(OBJS_SIGNALS) $(OBJS_SRC) $(OBJS_BUILTIN) $(OBJS_GNL) $(OBJS_UTILS) $(OBJS_PARSING) $(OBJS_HEREDOC) $(OBJS_EXECUTIONS)
	@$(CC) $(CFLAGS) $(OBJS_SIGNALS) $(OBJS_SRC) $(OBJS_EXECUTIONS) $(OBJS_BUILTIN) $(OBJS_GNL) $(OBJS_UTILS) $(OBJS_PARSING) $(OBJS_HEREDOC) $(LIBFT_LIB) -o $@ -lreadline

	@echo "$(GREEN)>>>	MINISHELL COMPILED	<<<"

$(LIBFT_LIB):
	@make --no-print-directory -C $(LIBFT_DIR) bonus

$(OBJ_PATH)%.o: $(PARSING_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(GNL_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(HEREDOC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(SIGNALS_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(BUILTIN_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(UTILS_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(EXECUTION_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(PARSING_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo ">>> $(RED)SUPPRESSION DES FICHIERS .o $(RESET)<<<"
	@rm -rf $(OBJ_PATH)
	@make --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@echo ">>> $(RED)SUPPRESSION DE L'EXECUTABLE $(RESET)<<<"
	@rm -f $(NAME)
	@make --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all
	@echo "$(RESET)"

.PHONY: all clean fclean re

