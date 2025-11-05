NAME = megaphone

SRC = megaphone.cpp

OBJ = ${SRC:.cpp=.o}

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(OBJ) -o $(NAME)

%.o: %.cpp
	c++ -Wall -Wextra -Werror -std=c++98 -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re