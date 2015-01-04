#!/bin/bash
OMP_OUTPUT="build/omp"

echo -e "# Running test 2 - Omp on large file multiple threads"
./$OMP_OUTPUT 1 inputs/4.jpg out/4_HSV_OMP.jpg
./$OMP_OUTPUT 2 inputs/4.jpg out/4_HSV_OMP.jpg
./$OMP_OUTPUT 4 inputs/4.jpg out/4_HSV_OMP.jpg
./$OMP_OUTPUT 6 inputs/4.jpg out/4_HSV_OMP.jpg
./$OMP_OUTPUT 8 inputs/4.jpg out/4_HSV_OMP.jpg
./$OMP_OUTPUT 16 inputs/4.jpg out/4_HSV_OMP.jpg