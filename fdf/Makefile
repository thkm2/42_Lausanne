NAME = fdf

CC = cc -Wall -Wextra -Werror

RM = rm -f

SRC = main.c init.c utils.c parse.c draw.c hook.c free.c command.c

OBJ = ${SRC:.c=.o}

#Mac
MLX_PATH = minilibx/
LIB_MLX = $(MLX_PATH)libmlx.a

#Linux
#MLX_PATH = minilibx-linux/
#LIB_MLX = $(MLX_PATH)libmlx.a

LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

GNL_PATH = get_next_line/
GNL = $(GNL_PATH)get_next_line.c $(GNL_PATH)get_next_line_utils.c

all: $(NAME)

#Mac
$(NAME): $(OBJ) $(LIBFT) $(LIB_MLX)
	$(CC) $(OBJ) $(GNL) $(LIBFT) $(LIB_MLX) -o $(NAME) -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

#Linux
#$(NAME): $(OBJ) $(LIBFT) $(LIB_MLX)
#	$(CC) $(OBJ) $(GNL) $(LIBFT) $(LIB_MLX) -o $(NAME) -L$(MLX_PATH) -lmlx -lGL -lX11 -lXext -lm

%.o: %.c
	$(CC) -c $< -o $@

$(LIB_MLX):
	make -C $(MLX_PATH)

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean
	make -C $(MLX_PATH) clean

re: fclean all

.PHONY: all clean fclean re