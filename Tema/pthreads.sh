#!/bin/bash
PTHREADS_OUTPUT="build/pthreads"

echo -e "# Running test 4 - Pthreads on large file multiple threads"
./$PTHREADS_OUTPUT 1 inputs/4.jpg out/4_HSV_OMP.jpg
./$PTHREADS_OUTPUT 2 inputs/4.jpg out/4_HSV_OMP.jpg
./$PTHREADS_OUTPUT 4 inputs/4.jpg out/4_HSV_OMP.jpg
./$PTHREADS_OUTPUT 6 inputs/4.jpg out/4_HSV_OMP.jpg
./$PTHREADS_OUTPUT 8 inputs/4.jpg out/4_HSV_OMP.jpg
./$PTHREADS_OUTPUT 16 inputs/4.jpg out/4_HSV_OMP.jpg