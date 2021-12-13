INCLUDES=-I includes/
CXXFLAGS=-std=c++11 -stdlib=libc++ -lc++abi -g -O0 -Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX=clang++

tests: bin/tests.out
	- $<

main: bin/main.out
	- $<
clean:
	rm -f bin/*

bin/main.out: main.cpp GraphData.cpp cs225/PNG.cpp cs225/HSLAPixel.cpp cs225/lodepng/lodepng.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests.out: GraphData.cpp cs225/PNG.cpp cs225/HSLAPixel.cpp cs225/lodepng/lodepng.cpp ./tests/test.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.DEFAULT_GOAL := main
.PHONY: clean main