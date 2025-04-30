CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

all: programa

programa: main.o 
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cc NIF.h Sequences.h SortMethod.h SortMethodTrace.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o programa
