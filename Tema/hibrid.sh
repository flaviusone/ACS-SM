#!/bin/bash
HIBRID_OUTPUT="build/hibrid"
module load libraries/openmpi-1.6-gcc-4.6.3

echo -e "# Running test 5 - Hybrid on large file multiple threads" >> hibrid
mpirun -n 1 ./$HIBRID_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> hibrid
mpirun -n 2 ./$HIBRID_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> hibrid
mpirun -n 4 ./$HIBRID_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> hibrid
mpirun -n 6 ./$HIBRID_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> hibrid
mpirun -n 8 ./$HIBRID_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> hibrid
mpirun -n 16 ./$HIBRID_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> hibrid