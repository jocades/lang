# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++20 -Wall

# Source files and output
SOURCES = main.cpp point.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

# Build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)

# Compile the .cpp files to .o object files
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

# Clean the build files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

