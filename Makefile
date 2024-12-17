CXX = g++
CXXFLAGS = -Iinclude -Ilibs -Wall -Wextra -O2
SOURCES = $(wildcard src/*.cpp) # pulls all iterations of .cpp in src
OBJECTS = $(SOURCES:src/%.cpp=obj/%.o) # gets all sources and replaces src/%.cpp to obj/%.o
TARGET = exec-main

# phony is important for making sure that commands get run even if there is a conflicting file name
# like make all, make clean, etc..
# some common ones are; all, clean, install, test, run.
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# % template for any potential .cpp that'll be turned to .o
# $@: expands to the complete FILENAME of current rule's target (the .o)
# $<: expands to the filename of the first PREQREQ for the current rule (the .cpp)
obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -rf obj $(TARGET)
