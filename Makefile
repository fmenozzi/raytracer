CC = g++ -std=c++11 -Wall -pedantic

CC_DEBUG = @$(CC) -g
CC_RELEASE = @$(CC) -O3

SRC = *.cpp

all: part1

part1:
	@$(CC_DEBUG) $(SRC) -o part1
	@./part1
	@eog part1.ppm 2>/dev/null &
