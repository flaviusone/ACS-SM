CC=gcc
CFLAGS = -Wall
LDFLAGS = -ljpeg

SIMPLE_PATH = src/simple.c
SIMPLE_OUTPUT = build/simple

all: build-simple

build-simple:
	$(CC) $(CFLAGS) $(SIMPLE_PATH) -o $(SIMPLE_OUTPUT) $(LDFLAGS)

clean:
	rm build/*