#!/bin/bash
echo "Running all experiments"
qsub -cwd -q ibm-opteron.q simple.sh
qsub -cwd -q ibm-opteron.q omp.sh
qsub -cwd -q ibm-opteron.q mpi.sh
qsub -cwd -q ibm-opteron.q pthreads.sh
qsub -cwd -q ibm-opteron.q hibrid.sh
