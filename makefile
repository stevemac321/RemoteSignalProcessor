# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -Iinc  # Add the include directory to the flags
LDFLAGS = -lncurses -pthread -lpcap
#-mavx2
# Target executable
TARGET = remote_monitor

# Source and header directories
SRC_DIR = src
INC_DIR = inc

# Source files (all .cpp files inside src/)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files (replace src/ with the root directory for object files)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=%.o)

# Build target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files into object files
%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to avoid conflicts with filenames
.PHONY: all clean
