#alonsuissa12@gmail.com 211344015

############################################################
#         make sure to install:                            #
#            1) wxWidgets                                  #
#            2) libcanberra-gtk-module                     #
############################################################

# Compiler
CXX := g++

# wxWidgets configuration
WX_CONFIG := wx-config

# Compiler and linker flags
CXXFLAGS := $(shell $(WX_CONFIG) --cxxflags)
LDFLAGS := $(shell $(WX_CONFIG) --libs)

# Target executable
TARGET := exe
TEST_TARGET := tests
# Source files
SRCS := demo.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Build the target
all: $(TARGET) $(TEST_TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(TEST_TARGET): Tests.o TestCounter.o
	$(CXX) -o $(TEST_TARGET) Tests.o TestCounter.o $(LDFLAGS)

# Compile the source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@



# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET) $(TEST_TARGET) Tests.o TestCounter.o
tree: all
	./exe

test: $(TEST_TARGET) Tree.hpp Node.hpp
	./tests

.PHONY: all clean tree test
