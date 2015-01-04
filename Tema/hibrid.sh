#!/bin/bash
HIBRID_OUTPUT="build/hibrid"

echo -e "# Running test 5 - Hybrid on large file multiple threads" >> hibrid
mpirun -n 10 ./$HIBRID_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> hibrid
mpirun -n 10 ./$HIBRID_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> hibrid
mpirun -n 10 ./$HIBRID_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> hibrid
mpirun -n 10 ./$HIBRID_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> hibrid
mpirun -n 10 ./$HIBRID_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> hibrid
mpirun -n 10 ./$HIBRID_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> hibrid