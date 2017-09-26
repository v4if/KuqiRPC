CPP = $(CXX)
CPPFLAGS = -std=c++11 -Wall -Wextra -O3
LDFLAGS = -pthread

NetworkSRC = $(shell find ../src/network -name '*.cpp')
NetworkHPP = $(shell find ../src/network -name '*.hpp')
NetworkOBJ = $(NetworkSRC:.cpp=.o)

all: network_test

network_test: $(NetworkOBJ) network.cpp
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf ../src/network/*.o
	rm -rf *_test