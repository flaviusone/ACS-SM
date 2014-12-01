#!/bin/bash
SIMPLE_OUTPUT="build/simple"
OMP_OUTPUT="build/omp"
MPI_OUTPUT="build/mpi"
PTHREADS_OUTPUT="build/pthreads"
HIBRID_OUTPUT="build/hibrid"

echo -e "Building files...\n"
make all
echo -e "Running tests...\n"

#Run test 1 - simple
echo -e "Running test 1 - simple...\n"
# ./$SIMPLE_OUTPUT inputs/uther_small.jpg out/uther_small_HSV.jpg
# ./$SIMPLE_OUTPUT inputs/TimpUltraHighRes.jpg out/TimpUltraHighRes_HSV.jpg
./$SIMPLE_OUTPUT inputs/nasa_world.jpg out/nasa_world_HSV.jpg

echo -e "\nRunning test 1 - omp...\n"
# ./$OMP_OUTPUT 4 inputs/uther_small.jpg out/uther_small_HSV_OMP.jpg
# ./$OMP_OUTPUT 1 inputs/nasa_world.jpg out/nasa_world_HSV_OMP.jpg
# ./$OMP_OUTPUT 2 inputs/nasa_world.jpg out/nasa_world_HSV_OMP.jpg
./$OMP_OUTPUT 4 inputs/nasa_world.jpg out/nasa_world_HSV_OMP.jpg

echo -e "\nRunning test 1 - mpi...\n"
# mpirun -n 10 ./$MPI_OUTPUT inputs/uther_small.jpg out/uther_small_HSV_MPI.jpg
mpirun -n 10 ./$MPI_OUTPUT inputs/nasa_world.jpg out/nasa_world_HSV_MPI.jpg

echo -e "\nRunning test 1 - pthreads...\n"
# ./$PTHREADS_OUTPUT 1 inputs/uther_small.jpg out/uther_small_HSV_PTHREADS.jpg
./$PTHREADS_OUTPUT 8 inputs/nasa_world.jpg out/nasa_world_HSV_PTHREADS.jpg

echo -e "\nRunning test 1 - hibrid...\n"
# mpirun -n 10 ./$HIBRID_OUTPUT inputs/uther_small.jpg out/uther_small_HSV_MPI_HIBRID.jpg
mpirun -n 10 ./$HIBRID_OUTPUT inputs/nasa_world.jpg out/nasa_world_HSV_HIBRID.jpg

echo -e "\nDone running tests"
make clean

