NAME = philo

CC = cc -Wall -Wextra -Werror

SRC = main.c utils.c parse.c init.c simulation.c supervisor.c

OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re