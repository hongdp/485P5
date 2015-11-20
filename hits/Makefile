# designate which compiler to use
CXX			= g++
# list of sources used in project
SOURCES 	= $(wildcard *.cpp)
# list of objects used in project
OBJECTS		= $(SOURCES:%.cpp=%.o)
# name of the executable produced by the top level
EXECUTABLE 	= eecs485pa5h
# name of the output file
OUTPUT_FILE = $(wildcard *.out)

#Default Flags
CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -Wvla -pedantic

# make release - will compile "all" with $(CXXFLAGS) and the -O3 flag
#				 also defines NDEBUG so that asserts will not check
release: CXXFLAGS += -O3 -DNDEBUG
release: all

# make debug - will compile "all" with $(CXXFLAGS) and the -g flag
#              also defines DEBUG so that "#ifdef DEBUG /*...*/ #endif" works
debug: CXXFLAGS += -g3 -DDEBUG
debug: clean all

# make profile - will compile "all" with $(CXXFLAGS) and the -pg flag
profile: CXXFLAGS += -pg
profile: clean all

# highest target; sews together all objects into executable
all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# rule for creating objects
%.o:
	$(CXX) $(CXXFLAGS) -c $*.cpp

# make clean - remove .o files, executable, tarball
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(SUBMIT_FILE) $(OUTPUT_FILE)

# these targets do not create any files
.PHONY: all release debug profile clean
# disable built-in rules
.SUFFIXES:
