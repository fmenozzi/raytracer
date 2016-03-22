CC = g++ -std=c++11 -Wall -pedantic

CC_DEBUG = @$(CC) -g
CC_RELEASE = @$(CC) -O3

SRC = src/*.cpp
INC = -Iinclude

GL_LFLAGS = -lGL -lGLU -lglut

all: part1 part2 part3

gl: part1-gl part2-gl part3-gl

no-omp: part1 part2 part3-no-omp

gl-no-omp: part1-gl part2-gl part3-gl-no-omp

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
	@$(CC_RELEASE) -fopenmp $(INC) part3.cpp $(SRC) -o part3 -DUSE_OPENMP
	@echo "Rendering..."
	@./part3
	@echo "Done"

part3-no-omp:
	@echo "Part 3 without OpenMP"
	@echo "Building..."
	@$(CC_RELEASE) $(INC) part3.cpp $(SRC) -o part3
	@echo "Rendering..."
	@./part3
	@echo "Done"

part1-gl:
	@echo "Part 1 using OpenGL"
	@echo "Building..."
	@$(CC_RELEASE) $(INC) part1.cpp $(SRC) -o part1 $(GL_LFLAGS) -DUSE_OPENGL
	@echo "Rendering..."
	@./part1 &
	@echo "Done"

part2-gl:
	@echo "Part 2 using OpenGL"
	@echo "Building..."
	@$(CC_RELEASE) $(INC) part2.cpp $(SRC) -o part2 $(GL_LFLAGS) -DUSE_OPENGL
	@echo "Rendering..."
	@./part2 &
	@echo "Done"

part3-gl:
	@echo "Part 3 using OpenGL"
	@echo "Building..."
	@$(CC_RELEASE) -fopenmp $(INC) part3.cpp $(SRC) -o part3 $(GL_LFLAGS) -DUSE_OPENGL -DUSE_OPENMP
	@echo "Rendering..."
	@./part3
	@echo "Done"

part3-gl-no-omp:
	@echo "Part 3 using OpenGL without OpenMP"
	@echo "Building..."
	@$(CC_RELEASE) $(INC) part3.cpp $(SRC) -o part3 $(GL_LFLAGS) -DUSE_OPENGL
	@echo "Rendering..."
	@./part3
	@echo "Done"

clean:
	@rm -f part1 part2 part3
