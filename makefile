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

# Source files
SRCS := demo.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Build the target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile the source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

tree: all
	./exe

.PHONY: all clean tree
