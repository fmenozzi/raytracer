CC = g++ -std=c++11 -Wall -pedantic

CC_DEBUG = @$(CC) -g
CC_RELEASE = @$(CC) -O3

SRC = src/*.cpp
INC = -Iinclude

all: part1 part2

part1:
	@echo "Part 1"
	@echo "Building..."
	@$(CC_DEBUG) $(INC) part1.cpp $(SRC) -o bin/part1
	@echo "Rendering..."
	@./bin/part1
	@echo "Done"
	@eog images/part1.ppm 2>/dev/null &

part2:
	@echo "Part 2"
	@echo "Building..."
	@$(CC_DEBUG) $(INC) part2.cpp $(SRC) -o bin/part2
	@echo "Rendering..."
	@./bin/part2
	@echo "Done"
	@eog images/part2.ppm 2>/dev/null &

part3:
	@echo "Part 3"
	@echo "Building..."
	@$(CC_DEBUG) $(INC) part3.cpp $(SRC) -o bin/part3
	@echo "Rendering..."
	@./bin/part3
	@echo "Done"
	@eog images/part3.ppm 2>/dev/null &
