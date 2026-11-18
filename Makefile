NAME        = ircserv

CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98

SRC_DIR     = src
INC_DIR     = includes

SRCS        = $(SRC_DIR)/main.cpp \
              $(SRC_DIR)/Message.cpp \
              $(SRC_DIR)/Parser.cpp

OBJS        = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
