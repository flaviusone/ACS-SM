#!/bin/bash
MPI_OUTPUT="build/mpi"
module load libraries/openmpi-1.6-gcc-4.6.3

echo -e "# Running test 3 - Mpi on large file multiple threads" >> mpi
mpirun -n 10 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 10 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 10 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 10 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 10 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 10 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi