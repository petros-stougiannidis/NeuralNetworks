# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude

# Source files and object files
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
TARGET = $(BINDIR)/my_program

# Create necessary directories if they don't exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

# Default target to build the project
all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

# Rule to compile each .cpp file into a .o object file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)

# Rebuild the project
rebuild: clean all
