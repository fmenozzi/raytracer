CC = g++ -std=c++11 -Wall -pedantic

CC_DEBUG = @$(CC) -g
CC_RELEASE = @$(CC) -O3

SRC = src/*.cpp
INC = -Iinclude

all: part1 part2

part1:
	@$(CC_DEBUG) $(INC) part1.cpp $(SRC) -o part1
	@./part1
	@eog part1.ppm 2>/dev/null &

part2:
	@$(CC_DEBUG) $(INC) part2.cpp $(SRC) -o part2
	@./part2
	@eog part2.ppm 2>/dev/null &
