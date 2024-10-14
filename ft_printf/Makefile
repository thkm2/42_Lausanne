NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

AR = ar -rcs

RM = rm -f

SRCS = ft_printf.c format_fonctions/ft_print_char.c format_fonctions/ft_print_string.c \
		format_fonctions/ft_print_ptr.c format_fonctions/ft_print_number.c \
		format_fonctions/ft_print_unsigned_number.c format_fonctions/ft_print_hex.c

OBJS = ${SRCS:.c=.o}

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
