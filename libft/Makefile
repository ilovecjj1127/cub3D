NAME = libft.a

SRC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
		get_next_line.c ft_abs.c ft_strjoin_free.c

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c\
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJ_DIR		=	obj/
OBJ			=	$(addprefix $(OBJ_DIR),$(SRC:%.c=%.o))

BONUS_OBJS = $(BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

HEADER = libft.h

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
		@ar rcs $(NAME) $(OBJ)
		@ranlib $(NAME)
		@echo "\n$(GREEN)$(NAME) created!$(DEFAULT)\n"

bonus: $(OBJ) $(BONUS_OBJS)
		cc $(CFLAGS) -c $(BONUS)
		ar rcs $(NAME) $(OBJ) $(BONUS_OBJS)

all: ${NAME}

clean:
		@rm -rf $(OBJ_DIR)

fclean: clean
		@rm -rf $(NAME)
		@echo "\n$(RED)$(NAME) removed!$(DEFAULT)\n\n"

re: fclean all

.PHONY: all clean fclean re bonus

# COLORS
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
DEFAULT	=	\033[0m