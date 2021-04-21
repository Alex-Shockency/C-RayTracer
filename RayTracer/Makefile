CC=g++ -I ./eigen3 -O3 -fopenmp -std=c++11

EXES = rayTracer 

all: rayTracer

rayTracer: rayTracer.cpp
	$(CC) -o raytracer rayTracer.cpp

model: model.cpp
	$(CC) -o model model.cpp

clean:
	rm -f $(EXES)