export CC = clang
export CXX = clang++

all: build

fresh: clean build

cmake:
	cmake -S . -B build -G Ninja

build: cmake
	ninja -C build

day1: build
	./build/aoc/day1

clean:
	rm -rf build

.PHONY: cmake build day1 clean