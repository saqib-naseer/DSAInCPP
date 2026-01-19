CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

run: main
	./main

clean:
	rm -f main

.PHONY: run clean
