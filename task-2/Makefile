CROSS =
CXX   = $(CROSS)g++
RM    = rm -f

all: main

main: main.cpp sha1.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -Wall -Wextra -std=c++11 -o $@ main.cpp

clean:
	$(RM) main
