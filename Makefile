# SETUP
NAME		=	cub3d
MLX			=	$(MLX_PATH)libmlx42.a
LIBFT		=	$(LFT_PATH)libft.a

CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address
RM			=	rm -rf
LIB_CF		=	-L $(LFT_PATH) -lft
OS			=	$(shell uname -s)

ifeq ($(OS),Linux)
			MLX_CF = $(MLX_PATH)libmlx42.a -I $(MLX_H_PATH) -ldl -lglfw -pthread -lm
else
			MLX_CF = $(MLX_PATH)libmlx42.a -lglfw -I $(MLX_H_PATH)
endif

INCLUDES	=	-I$(HEADER_DIR) -I$(LFT_PATH) -I$(MLX_H_PATH)

# FILES AND PATH
LFT_PATH 	=	libft/
MLX_DIR		=	MLX42/
MLX_H_PATH 	=	MLX42/include/
MLX_PATH	=	MLX42/build/

HEADER_FILE	=	cub3d.h
HEADER_DIR	=	include/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_FILE))

SRC_FILES	=	main.c \
				raycasting.c \
				render.c \
				move.c \
				rotate.c

SRC_DIR		=	src/
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		=	obj/
OBJ			=	$(addprefix $(OBJ_DIR),$(SRC_FILES:%.c=%.o))


# RULES
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		cc $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER) $(LIBFT) $(MLX)
		@echo "\n$(YELLOW)Generating $(NAME) executable...$(DEFAULT)\n"
		cc $(OBJ) $(CFLAGS) $(LIB_CF) $(MLX_CF) -o $(NAME)
		@echo "\n$(GREEN)$(NAME) created!$(DEFAULT)\n"

$(MLX): $(MLX_PATH)
		@echo "\n$(YELLOW)Generating MLX42 ...$(DEFAULT)\n"
		@cmake $(MLX_DIR) -B $(MLX_PATH)
		@make -C $(MLX_PATH) -j4
		@echo "\n$(GREEN)MLX42 created$(DEFAULT)\n"

$(LIBFT): $(LFT_PATH)
		@echo "\n$(YELLOW)Generating Libft...$(DEFAULT)\n"
		@make -C $(LFT_PATH)
		@echo "\n$(GREEN)Libft created!$(DEFAULT)\n"

clean: 
		@make clean -C $(LFT_PATH)
		@echo "\n$(RED)Libft objects removed!$(DEFAULT)\n\n"
		@$(RM) $(OBJ_DIR)
		@echo "\n$(RED)$(NAME) objects removed!$(DEFAULT)\n\n"

fclean: clean
		@make fclean -C $(LFT_PATH)
		@$(RM) $(MLX_PATH)
		@echo "\n$(RED)All libraries removed!$(DEFAULT)\n\n"
		@$(RM) $(NAME)
		@echo "\n$(RED)$(NAME) removed!$(DEFAULT)\n\n"

re: fclean all

.PHONY: all clean fclean re

# COLORS
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
DEFAULT	=	\033[0m