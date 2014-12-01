#!/bin/bash
rm STDIN.*
qsub -q ibm-nehalem12.q -cwd <<EOF
module load compilers/gnu-4.6.3
module load libraries/openmpi-1.6-gcc-4.6.3
export OMP_NUM_THREADS=4
./run_tests.sh > result
EOF
#module load libraries/openmpi-1.6-gcc-4.6.3
