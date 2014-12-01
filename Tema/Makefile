CC=gcc
MPICC=mpicc
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

HIBRID_PATH = src/hibrid.c
HIBRID_OUTPUT = build/hibrid

all: build-simple build-omp build-mpi build-pthreads build-hibrid

build-simple:
	$(CC) $(CFLAGS) $(SIMPLE_PATH) -o $(SIMPLE_OUTPUT) $(LDFLAGS)

build-omp:
	$(CC) -fopenmp $(CFLAGS) $(OMP_PATH) -o $(OMP_OUTPUT) $(LDFLAGS)

build-mpi:
	$(MPICC) $(CFLAGS) $(MPI_PATH) -o $(MPI_OUTPUT) $(LDFLAGS)

build-hibrid:
	$(MPICC) -fopenmp $(CFLAGS) $(HIBRID_PATH) -o $(HIBRID_OUTPUT) $(LDFLAGS)

build-pthreads:
	$(CC) $(CFLAGS) $(PTHREADS_PATH) -o $(PTHREADS_OUTPUT) $(LDFLAGS) -lpthread

clean:
	rm build/*