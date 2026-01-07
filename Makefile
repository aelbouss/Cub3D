NAME = cub3d

CC = cc
CFLAGS = -Wall -Werror -Wextra -O3
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_FLAGS = -Lminilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz

SRCS = $(wildcard srcs/parsing/*.c) $(wildcard srcs/Raycasting/*.c) srcs/main.c  

OBJS = $(SRCS:.c=.o)

HEADER = $(wildcard includdes/ *.h)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I/usr/include -Iminilibx-linux -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
.SECONDARY :$(OBJS)
