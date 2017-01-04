CC = g++ -std=c++11 -Wall -pedantic

CC_DEBUG = @$(CC) -g
CC_RELEASE = @$(CC) -O3

SRC = src/*.cpp deps/argparser/c/argparser.c deps/easyppm/easyppm.c
INC = -Iinclude -Ideps -Ideps/argparser/c -Ideps/easyppm

GL_LFLAGS = -lGL -lGLU -lglut

all: ppm

ppm: build-ppm part1-ppm part2-ppm part3-ppm part4-ppm part5a-ppm part5b-ppm clean
gl: build-gl part1-gl part2-gl part3-gl part4-gl part5a-gl part5b-gl clean
no-omp: build-ppm-no-omp part1-ppm part2-ppm part3-ppm part4-ppm part5a-ppm part5b-ppm clean
gl-no-omp: build-gl-no-omp part1-gl part2-gl part3-gl part4-gl part5a-gl part5b-gl clean

build-ppm: build-part1-ppm build-part2-ppm build-part3-ppm build-part4-ppm build-part5-ppm
build-ppm-no-omp: build-part1-ppm build-part2-ppm build-part3-ppm-no-omp build-part4-ppm-no-omp build-part5-ppm
build-gl: build-part1-gl build-part2-gl build-part3-gl build-part4-gl build-part5-gl
build-gl-no-omp: build-part1-gl build-part2-gl build-part3-gl-no-omp build-part4-gl-no-omp build-part5-gl

# Build
build-part1-ppm:
	@echo "Building Part 1..."
	@$(CC_RELEASE) $(INC) part1.cpp $(SRC) -o part1
	@echo "Done"
build-part1-gl:
	@echo "Building Part 1 with OpenGL..."
	@$(CC_RELEASE) $(INC) part1.cpp $(SRC) -o part1 $(GL_LFLAGS) -DUSE_OPENGL
	@echo "Done"
build-part2-ppm:
	@echo "Building Part 2..."
	@$(CC_RELEASE) $(INC) part2.cpp $(SRC) -o part2
	@echo "Done"
build-part2-gl:
	@echo "Building Part 2 with OpenGL..."
	@$(CC_RELEASE) $(INC) part2.cpp $(SRC) -o part2 $(GL_LFLAGS) -DUSE_OPENGL
	@echo "Done"
build-part3-ppm:
	@echo "Building Part 3..."
	@$(CC_RELEASE) -fopenmp $(INC) part3.cpp $(SRC) -o part3 -DUSE_OPENMP
	@echo "Done"
build-part3-ppm-no-omp:
	@echo "Building Part 3 without OpenMP..."
	@$(CC_RELEASE) $(INC) part3.cpp $(SRC) -o part3
	@echo "Done"
build-part3-gl:
	@echo "Building Part 3 with OpenGL..."
	@$(CC_RELEASE) -fopenmp $(INC) part3.cpp $(SRC) -o part3 $(GL_LFLAGS) -DUSE_OPENGL
	@echo "Done"
build-part3-gl-no-omp:
	@echo "Building Part 3 with OpenGL, OpenMP..."
	@$(CC_RELEASE) $(INC) part3.cpp $(SRC) -o part3 $(GL_LFLAGS) -DUSE_OPENGL
	@echo "Done"
build-part4-ppm:
	@echo "Building Part 4..."
	@$(CC_RELEASE) -fopenmp $(INC) part4.cpp $(SRC) -o part4 -DUSE_OPENMP
	@echo "Done"
build-part4-ppm-no-omp:
	@echo "Building Part 4 without OpenMP..."
	@$(CC_RELEASE) $(INC) part4.cpp $(SRC) -o part4
	@echo "Done"
build-part4-gl:
	@echo "Building Part 4 with OpenGL..."
	@$(CC_RELEASE) -fopenmp $(INC) part4.cpp $(SRC) -o part4 $(GL_LFLAGS) -DUSE_OPENGL
	@echo "Done"
build-part4-gl-no-omp:
	@echo "Building Part 4 with OpenGL, OpenMP..."
	@$(CC_RELEASE) $(INC) part4.cpp $(SRC) -o part4
	@echo "Done"
build-part5-ppm:
	@echo "Building Part 5..."
	@$(CC_RELEASE) $(INC) part5.cpp $(SRC) -o part5
	@echo "Done"
build-part5-gl:
	@echo "Building Part 5 with OpenGL..."
	@$(CC_RELEASE) $(INC) part5.cpp $(SRC) -o part5 $(GL_LFLAGS) -DUSE_OPENGL
	@echo "Done"

# Render
part1-ppm:
	@echo "Rendering Part 1..."
	@./part1
	@echo "Done"
part1-gl:
	@echo "Rendering Part 1 with OpenGL..."
	@./part1 &
	@echo "Done"
part2-ppm:
	@echo "Rendering Part 2..."
	@./part2
	@echo "Done"
part2-gl:
	@echo "Rendering Part 2 with OpenGL..."
	@./part2 &
	@echo "Done"
part3-ppm:
	@echo "Rendering Part 3..."
	@./part3
	@echo "Done"
part3-gl:
	@echo "Rendering Part 3 with OpenGL..."
	@./part3 &
	@echo "Done"
part4-ppm:
	@echo "Rendering Part 4..."
	@./part4
	@echo "Done"
part4-gl:
	@echo "Rendering Part 4 with OpenGL..."
	@./part4 &
	@echo "Done"
part5a-ppm:
	@echo "Rendering Part 5 (no shadows)..."
	@./part5
	@echo "Done"
part5a-gl:
	@echo "Rendering Part 5 (no shadows) with OpenGL..."
	@./part5 &
	@echo "Done"
part5b-ppm:
	@echo "Rendering Part 5 (with shadows)..."
	@./part5 --shadows
	@echo "Done"
part5b-gl:
	@echo "Rendering Part 5 (with shadows) with OpenGL..."
	@./part5 --shadows &
	@echo "Done"

# Clean
clean:
	@rm -f part1 part2 part3 part4 part5
