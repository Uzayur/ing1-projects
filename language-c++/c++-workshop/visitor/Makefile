CXXFLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic

CXX=g++

OBJS=visitor-test.o builder.o tree.o \
    node.o leaf.o compute-visitor.o

TARGET=visitor

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

clean:
	$(RM) $(TARGET) $(OBJS)
