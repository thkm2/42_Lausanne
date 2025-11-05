NAME = animal

FLAGS = -Wall -Wextra -Werror -std=c++98

SRC_PATH = src/
SRC = $(SRC_PATH)Animal.cpp  $(SRC_PATH)Cat.cpp  $(SRC_PATH)Dog.cpp  $(SRC_PATH)main.cpp  $(SRC_PATH)WrongAnimal.cpp  $(SRC_PATH)WrongCat.cpp $(SRC_PATH)Brain.cpp

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