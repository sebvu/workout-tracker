CXX = g++
PYTHON = python
CXXFLAGS = -Iinclude -Iinclude/enums -Wall -Wextra -O2
SOURCES = $(wildcard src/*.cpp) # pulls all iterations of .cpp in src
OBJECTS = $(SOURCES:src/%.cpp=obj/%.o) # gets all sources and replaces src/%.cpp to obj/%.o
TARGET = exec-main
CONFIG_FILE = config.toml
ENUMS_CREATOR = $(CURDIR)/helpers/enumsCreator.py
CUSTOM_ENUMS = $(CURDIR)/include/enums/

# phony is important for making sure that commands get run even if there is a conflicting file name
# like make all, make clean, etc..
# some common ones are; all, clean, install, test, run.
.PHONY: all clean run-enums

all: enums $(TARGET)

enums:
	mkdir -p $(CUSTOM_ENUMS)
	$(PYTHON) $(ENUMS_CREATOR)

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
	rm -rf obj $(TARGET) $(CUSTOM_ENUMS)

run:
	@if [ ! -f $(TARGET) ]; then \
		echo "Executable not found. Please run make first."; \
		exit 1; \
	elif [ ! -f $(CONFIG_FILE) ]; then \
		echo "Config file not found. Please refer to https://github.com/sebvu/workout-tracker for config file."; \
		exit 1; \
	elif [ ! -f $(CUSTOM_ENUMS) ]; then \
		echo  "Custom enums has not been created. Please run make enums first."; \
		exit 1; \
	fi; \
	./$(TARGET) $(CONFIG_FILE) 
