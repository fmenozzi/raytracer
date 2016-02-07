CC = g++ -std=c++11 -Wall -pedantic

CC_DEBUG = @$(CC) -g
CC_RELEASE = @$(CC) -O3

SRC = src/*.cpp
INC = -Iinclude

all: part2

part2:
	@$(CC_DEBUG) $(INC) part2.cpp $(SRC) -o ../bin/part2
	@../bin/part2
	@eog ../images/part2.ppm 2>/dev/null &
