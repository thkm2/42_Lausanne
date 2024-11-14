NAME = push_swap

LIB = push_swap.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

AR = ar -rcs

RM = rm -rf

SRCS = main.c error.c push.c reverse_rotate.c rotate.c \
       stack_init.c stack_utils.c swap.c tiny_sort.c \
	   push_swap_command.c push_swap_init.c split.c

OBJS = ${SRCS:.c=.o}

$(NAME): $(LIB)
	$(CC) $(CFLAGS) main.c $(LIB) -o $(NAME)

$(LIB):	$(OBJS)
	$(AR) $(LIB) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(LIB)

re: fclean all

.PHONY: all clean fclean re