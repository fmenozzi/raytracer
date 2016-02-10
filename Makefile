CC = g++ -std=c++11 -Wall -pedantic

CC_DEBUG = @$(CC) -g
CC_RELEASE = @$(CC) -O3

SRC = src/*.cpp
INC = -Iinclude

all: part1 part2 part3

part1:
	@echo "Part 1"
	@echo "Building..."
	@$(CC_RELEASE) $(INC) part1.cpp $(SRC) -o part1
	@echo "Rendering..."
	@./part1
	@echo "Done"

part2:
	@echo "Part 2"
	@echo "Building..."
	@$(CC_RELEASE) $(INC) part2.cpp $(SRC) -o part2
	@echo "Rendering..."
	@./part2
	@echo "Done"

part3:
	@echo "Part 3"
	@echo "Building..."
	@$(CC_RELEASE) -fopenmp $(INC) part3.cpp $(SRC) -o part3
	@echo "Rendering..."
	@./part3
	@echo "Done"

clean:
	@rm part1 part2 part3
