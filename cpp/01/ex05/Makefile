NAME = harl

FLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp Harl.cpp

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