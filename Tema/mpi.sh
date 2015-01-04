#!/bin/bash
MPI_OUTPUT="build/mpi"
module load libraries/openmpi-1.6-gcc-4.6.3

echo -e "# Running test 3 - Mpi on large file multiple threads" >> mpi
mpirun -n 1 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 2 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 4 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 6 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 8 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 16 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi