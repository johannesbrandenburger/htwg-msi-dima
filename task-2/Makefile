CROSS =
CXX   = $(CROSS)g++
RM    = rm -f

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -Wall -Wextra -std=c++11 -o $@ main.cpp -lssl -lcrypto

clean:
	$(RM) main