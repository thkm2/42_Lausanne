NAME = webserv
CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98
SRCS =  srcs/Config.cpp \
		srcs/ConfigParser.cpp \
		srcs/Lexer.cpp \
		srcs/RequestManager.cpp \
		srcs/SocketManager.cpp \
		srcs/utils.cpp \
		srcs/main.cpp
		
OBJS = $(patsubst srcs/%.cpp, obj/%.o, $(SRCS))

all: $(NAME)

obj/%.o: srcs/%.cpp
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
