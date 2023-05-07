# Variables
SRC_DIR = src
OUT_DIR = out
BIN_DIR = bin
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -I$(SRC_DIR)

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)

# Executable file
EXEC = $(BIN_DIR)/my_program

# Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR) $(BIN_DIR)

.PHONY: all clean
