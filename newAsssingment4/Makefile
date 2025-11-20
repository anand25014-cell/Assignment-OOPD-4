# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -pthread

# Folders
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files (mapped from src → obj)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Executable name
TARGET = student_tracker

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each .cpp → .o inside obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory if not present
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Run the app
run: $(TARGET)
	./$(TARGET)

# FULL CLEAN: removes all .o files and the executable
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean run
