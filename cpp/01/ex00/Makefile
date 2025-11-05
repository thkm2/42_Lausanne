NAME = zombie

FLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp newZombie.cpp randomChump.cpp  Zombie.cpp

OBJ = ${SRC:.cpp=.o}

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	c++ $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re