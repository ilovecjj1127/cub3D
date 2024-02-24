NAME	= parsing_test
LIBFT	= ../libft/libft.a

OBJ_DIR	= .obj

SRCS = 	test.c parsing.c

OBJS	= ${SRCS:%.c=$(OBJ_DIR)/%.o}

CC = cc
CFLAGS	= -Wall -Wextra -Werror -I../include -I../libft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^

$(LIBFT):
	$(MAKE) -C ../libft -f Makefile

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: make clean fclean re