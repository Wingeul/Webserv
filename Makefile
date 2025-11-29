CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Iincludes


SRC_DIR = srcs
OBJ_DIR = obj
BIN = webserv

SRCS = \
    $(SRC_DIR)/client_side/client_socket.cpp \
    $(SRC_DIR)/request_parsing/start_line.cpp \
	$(SRC_DIR)/request_parsing/headers.cpp \
	$(SRC_DIR)/request_parsing/body.cpp \
    $(SRC_DIR)/server_side/handle_request.cpp \
    $(SRC_DIR)/server_side/loop.cpp \
    $(SRC_DIR)/utils/utils.cpp

OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))


all: $(BIN)


$(BIN): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(BIN)

re: fclean all

.PHONY: all clean fclean re
