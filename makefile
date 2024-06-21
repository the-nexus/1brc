
CXX=g++
CXX_ARGS=-Wall -std=c++20

all: obrc

obrc: build/main.o build/solution_a.o
	$(CXX) $(CXX_ARGS) -o obrc build/main.o build/solution_a.o

build/main.o: source/main.cpp
	mkdir -p build
	$(CXX) $(CXX_ARGS) -c source/main.cpp -o build/main.o
	
build/solution_a.o: source/solution_a.cpp
	mkdir -p build
	$(CXX) $(CXX_ARGS) -c source/solution_a.cpp -o build/solution_a.o

clean:
	rm -rf build
	rm -f obrc
