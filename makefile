# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -g
LDFLAGS = -lncurses  -pthread -lpcap

# Target executable
TARGET = remote_monitor

# Source files
SRCS = main.cpp windraw.cpp voltage_info.cpp sock.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to avoid conflicts with filenames
.PHONY: all clean
