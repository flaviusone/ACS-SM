all: simple omp mpi pthr

simple: code.cpp
	g++ -O3 -o code_simple code.cpp -ljpeg -lm

omp: code.cpp
	g++ -O3 -o code_omp code.cpp -ljpeg -lm -fopenmp -DOMP

mpi: code.cpp
	mpic++ -O3 -o code_mpi code.cpp -ljpeg -lm -DMPI_MODE

pthr: code.cpp
	g++ -O3 -o code_pthread code.cpp -ljpeg -lm -lpthread -DPTHREADS_MODE
