CROSS =
CXX   = $(CROSS)g++
RM    = rm -f

all: main nested-loops

main: main.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -Wall -Wextra -std=c++11 -o $@ main.cpp -lssl -lcrypto

nested-loops: nested-loops.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -Wall -Wextra -std=c++11 -o $@ nested-loops.cpp -lssl -lcrypto

clean:
	$(RM) main nested-loops