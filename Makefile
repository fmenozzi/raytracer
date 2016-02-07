CC = g++ -std=c++11 -Wall -pedantic

CC_DEBUG = @$(CC) -g
CC_RELEASE = @$(CC) -O3

SRC = src/*.cpp
INC = -Iinclude

all: part1

part1:
	@$(CC_DEBUG) $(INC) part1.cpp $(SRC) -o bin/part1
	@./bin/part1
	@eog images/part1.ppm 2>/dev/null &
