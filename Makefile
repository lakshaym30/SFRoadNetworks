INCLUDES=-I includes/

OBJS = PNG.o HSLAPixel.o lodepng.o GraphData
CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm



main: bin/main.out
	- $<



bin/main.out: main.cpp GraphData.o PNG.o HSLAPixel.o lodepng.o
	$(CXX) $(CXXFLAGS) $^ -o $@



PNG.o: cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

HSLAPixel.o: cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

lodepng.o: cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp

GraphData.o: GraphData.cpp GraphData.h
	g++ -std=c++11 -c GraphData.cpp

test: test.o tests/catch.hpp GraphData.o
	$(CXX) tests/test.cpp 

test.o: test.cpp catch.hpp
	g++ -std=c++11 -c tests/test.cpp

clean:
	rm -f *.o $(EXENAME) test

.DEFAULT_GOAL := main
.PHONY: clean main test