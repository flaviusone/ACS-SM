#!/bin/bash
MPI_OUTPUT="build/mpi"

echo -e "# Running test 3 - Mpi on large file multiple threads" >> mpi
mpirun -n 10 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 10 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 10 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 10 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 10 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi
mpirun -n 10 ./$MPI_OUTPUT inputs/4.jpg out/4_HSV_MPI.jpg >> mpi