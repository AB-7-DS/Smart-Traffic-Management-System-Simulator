# usage:
# to compile the programm type "make" in the terminal
# to run the programm type "./app" in the terminal
# to clean the files type "make clean" in the terminal
# Warning: the make clean command will delete all the object files, the executable file and the dependency files so you will have to recompile the programm


CXX = g++

# note: this command compiles the programm without making dependency files or warnings
CXXFLAGS = -std=c++11 

# note: this command compiles the programm with making dependency files and warnings
# CXXFLAGS = -std=c++11 -Wall -MMD

SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)
TARGET = app
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(SFML_FLAGS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
-include $(DEPS)
clean:
	rm -f $(OBJS) $(TARGET) $(DEPS)
.PHONY: all clean