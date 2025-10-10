NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = srcs/cub3d.c srcs/get_next_line.c srcs/get_next_line_utils.c\
srcs/environement_setup.c srcs/tilset_handling.c srcs/key_hook_handling.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lminilibx-linux -lmlx -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME)

srcs/%.o : srcs/%.c
	$(CC) $(CFLAGS) -g -I/usr/include -Iminilibx-linux -O3 -c $< -o $@
clean:
	rm -rf $(OBJS)
fclean: clean
	rm -r $(NAME)
re : fclean
	$(MAKE) all
.SECONDARY: $(OBJS)
.PHONNY: all clean fclean re
