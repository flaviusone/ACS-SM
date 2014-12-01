#!/bin/bash
SIMPLE_OUTPUT="build/simple"
OMP_OUTPUT="build/omp"
MPI_OUTPUT="build/mpi"
PTHREADS_OUTPUT="build/pthreads"

echo -e "Building files...\n"
make all
echo -e "Running tests...\n"

#Run test 1 - simple
echo -e "Running test 1 - simple...\n"
./$SIMPLE_OUTPUT inputs/uther_small.jpg out/uther_small_HSV.jpg
# ./$SIMPLE_OUTPUT inputs/TimpUltraHighRes.jpg out/TimpUltraHighRes_HSV.jpg
# ./$SIMPLE_OUTPUT inputs/nasa_world.jpg out/nasa_world_HSV.jpg

echo -e "\nRunning test 1 - omp...\n"
# ./$OMP_OUTPUT inputs/uther_small.jpg out/uther_small_HSV.jpg
./$OMP_OUTPUT 1 inputs/nasa_world.jpg out/nasa_world_HSV.jpg
./$OMP_OUTPUT 2 inputs/nasa_world.jpg out/nasa_world_HSV.jpg
./$OMP_OUTPUT 4 inputs/nasa_world.jpg out/nasa_world_HSV.jpg

echo -e "\nDone running tests"
make clean

