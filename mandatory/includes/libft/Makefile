CC = cc
SRC = ft_bzero.c \
	  ft_isalpha.c \
	  ft_isdigit.c \
	  ft_memchr.c \
	  ft_memcpy.c \
	  ft_memset.c \
	  ft_strlcat.c \
	  ft_strlen.c \
	  ft_strnstr.c \
	  ft_tolower.c \
	  ft_atoi.c  \
	  ft_isalnum.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_memcmp.c \
	  ft_memmove.c \
	  ft_strchr.c \
	  ft_strlcpy.c \
	  ft_strncmp.c \
	  ft_strrchr.c \
	  ft_toupper.c \
	  ft_calloc.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_split.c \
	  ft_itoa.c \
	  ft_strmapi.c \
	  ft_striteri.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_strdup.c \
	  ft_substr.c \
	  ft_free_split.c \
	  get_next_line_bonus.c

BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OBJ = $(SRC:%.c=o_files/%.o)
B_OBJ = $(BONUS:%.c=o_files/%.o)
NAME = libft.a
CFLAGS = -Werror -Wextra -Wall -g

.PHONY : all clean fclean re bonus

all : $(NAME)

$(NAME) : $(OBJ)
	@ar -rcs $(NAME) $^
	@echo "Library $(NAME) created."

bonus : $(OBJ) $(B_OBJ)
	@ar -rcs $(NAME) $^

o_files/%.o : %.c
	@mkdir -p o_files 
	@$(CC) -o $@ -c $< $(CFLAGS)
	
clean : 
	@rm -f o_files/*.o

fclean : clean
	@rm -f $(NAME)

re : fclean all

