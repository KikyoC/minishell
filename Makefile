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

OBJ_PATH = obj/
SRC_PATH = mandatory/src/
# SIGNALS_PATH = mandatory/signals/
# UTILS_PATH = mandatory/utils/
# PARSING_PATH = mandatory/parsing/

SRC = main.c
# UTIL = 
# SIGNAL = 
# PARSING = 

SRCS = $(addprefix $(SRC_PATH), $(SRC))
# UTILS = $(addprefix $(SRC_PATH), $(UTIL))
# SIGNALS = $(addprefix $(SRC_PATH), $(SIGNAL))
# PARSINGS = $(addprefix $(PARSING_PATH), $(PARSING))

OBJ_SRC = $(SRC:.c=.o)
# OBJ_UTILS = $(UTIL:.c=.o)
# OBJ_SIGNALS = $(SIGNAL:.c=.o)
# OBJ_PARSING = $(PARSING:.c=.o)

OBJS_SRC = $(addprefix $(OBJ_PATH), $(OBJ_SRC))
# OBJS_UTILS = $(addprefix $(OBJ_PATH), $(OBJ_UTILS))
# OBJS_PARSING = $(addprefix $(OBJ_PATH), $(OBJ_PARSING))
# OBJS_SIGNALS = $(addprefix $(OBJ_PATH), $(OBJ_SIGNALS))

LIBFT_LIB = $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))

BARS := "▰▰▱▱▱▱▱▱▱▱▱ 17%" "▰▰▰▱▱▱▱▱▱▱▱ 23%" "▰▰▰▰▱▱▱▱▱▱▱ 38%" "▰▰▰▰▰▱▱▱▱▱▱ 42%" "▰▰▰▰▰▰▱▱▱▱▱ 51%" \
	"▰▰▰▰▰▰▰▱▱▱▱ 65%" "▰▰▰▰▰▰▰▰▱▱▱ 79%" "▰▰▰▰▰▰▰▰▰▱▱ 87%" "▰▰▰▰▰▰▰▰▰▰ 94%" "▰▰▰▰▰▰▰▰▰▰ 100%" \

all: $(NAME)
	@:	

$(NAME): $(OBJS_SRC) $(LIBFT_LIB) $(OBJS_GNL)
	@$(CC) $(CFLAGS) $(OBJS_SRC) $(OBJS_GNL) $(LIBFT_LIB) -o $@
	@echo "$(GREEN)>>>	MINISHELL COMPILED	<<<"

$(LIBFT_LIB):
	@make --no-print-directory -C $(LIBFT_DIR)

$(OBJ_PATH)%.o: $(PARSING_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(GNL_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(SIGNAL_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(UTILS_PATH)%.c
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

