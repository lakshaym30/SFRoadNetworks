INCLUDES=-I includes/
CXXFLAGS=-std=c++20 -stdlib=libc++ -lc++abi -g -O0 -Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX=clang++

main: bin/main.out
	- $<

clean:
	rm -f bin/*

bin/main.out: main.cpp GraphData.cpp cs225/PNG.cpp cs225/HSLAPixel.cpp cs225/lodepng/lodepng.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.DEFAULT_GOAL := main
.PHONY: clean main