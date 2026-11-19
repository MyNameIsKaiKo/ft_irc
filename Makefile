NAME        = ircserv

CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98

SRC_DIR     = src
PARSER_DIR  = src/parser
NETWORK_DIR = src/network
DATA_DIR	= src/data
INC_DIR     = includes

SRCS        = $(SRC_DIR)/main.cpp \
              $(PARSER_DIR)/Message.cpp \
              $(PARSER_DIR)/Parser.cpp \
			  $(NETWORK_DIR)/init_server.cpp \
			  $(NETWORK_DIR)/NetworkData.cpp 

			  

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
