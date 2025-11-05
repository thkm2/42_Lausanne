NAME = weapon

FLAGS = -Wall -Wextra -Werror -std=c++98

SRC = HumanA.cpp  HumanB.cpp  main.cpp  Weapon.cpp

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
