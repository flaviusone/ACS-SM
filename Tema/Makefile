CC=gcc
CFLAGS = -Wall
LDFLAGS = -ljpeg

SIMPLE_PATH = src/simple.c
SIMPLE_OUTPUT = build/simple

OMP_PATH = src/omp.c
OMP_OUTPUT = build/omp

MPI_PATH = src/mpi.c
MPI_OUTPUT = build/mpi

PTHREADS_PATH = src/pthreads.c
PTHREADS_OUTPUT = build/pthreads

all: build-simple build-omp build-mpi build-pthreads

build-simple:
	$(CC) $(CFLAGS) $(SIMPLE_PATH) -o $(SIMPLE_OUTPUT) $(LDFLAGS)

build-omp:
	$(CC) -fopenmp $(CFLAGS) $(OMP_PATH) -o $(OMP_OUTPUT) $(LDFLAGS)

build-mpi:
	$(CC) $(CFLAGS) $(MPI_PATH) -o $(MPI_OUTPUT) $(LDFLAGS)

build-pthreads:
	$(CC) $(CFLAGS) $(PTHREADS_PATH) -o $(PTHREADS_OUTPUT) $(LDFLAGS)

clean:
	rm build/*