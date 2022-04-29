CC=clang
CXX=clang++

CFLAGS=-Wall -Werror -pedantic -std=c++17 

SRC=src/main.cpp src/impl/benchmark.cpp
INCLUDE=include/

LIBS=pthread

NAME=collatz-bench

all: release strip
	echo Done!

debug:
	mkdir -p build
	$(CXX) -I$(INCLUDE) -l$(LIBS) $(CFLAGS) -g -O0 $(SRC) -o build/$(NAME)-debug

release:
	mkdir -p build
	$(CXX) -I$(INCLUDE) -l$(LIBS) $(CFLAGS) -O3 $(SRC) -o build/$(NAME)

strip: 
	strip build/$(NAME)

clean:
	rm -rf build
