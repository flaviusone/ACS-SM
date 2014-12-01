/**
*
* Author: Flavius Tirnacop
* Grupa: 341C1
* Fisier: mpi.c
* Descriere: Implementare seriala transformare RGB->HSV
*
**/

/*==========  Includes & Defines  ==========*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/time.h>
#include "mpi.h"
#include "jpeg_functions.h"


#define MIN2(A,B)       ((A)<(B)?(A):(B))
#define MIN(A,B,C)     (MIN2(MIN2((A),(B)),(C)))

#define MAX2(A,B)       ((A)>(B)?(A):(B))
#define MAX(A,B,C)     (MAX2(MAX2((A),(B)),(C)))

/*-----  End of Includes & Defines  ------*/

void RGBtoHSV(uint8_t *src){
	float min, max, delta;
	float r, g, b, h, s, v;

	r = src[0];
	g = src[1];
	b = src[2];

	min = MIN(src[0], src[1], src[2]);
    max = MAX(src[0], src[1], src[2]);

    delta = max - min;

	/* Valoarea pentru V */
    v = max;

    if(max != 0)
    {
    	/* Valoarea pentru S */
    	s = delta / max;
    }
    else
    {
    	/* r = g = b = 0 */
    	s = 0;
    	h = -1;
    	src[0] = h; src[1] = s; src[2] = v;
    	return;
    }

    if(r == max)
    	h = (g - b) / delta;
    else if(g == max)
    	h = 2 + (b - r) / delta;
    else
    	h = 4 + (r - g) / delta;

    h *= 60;
    if(h < 0)
    	h += 360;

    src[0] = (h / 360.) * 255;
    src[1] = delta * 255 / max;
    src[2] = max;
}

int main(int argc, char **argv){
	/*==========  Variabile declarate  ==========*/
	struct timeval start,finish;
    double t;                   /* Var pentru calcul timp */
    uint8_t* image;             /* Imaginea originala */
    uint8_t* image_chunk;       /* Bucata de imagine pentru fiecare proces */
    int chunk_size;             /* Dimensiune chunk proces */
    int width,height;           /* Lungime si latime imagine */
    int *w,*h;                  /* Aux */
    int i, rc, numtasks, rank;  /* Aux (MPI) */
	/*-----  End of Variabile declarate  ------*/

    /*==========  MPI Inits  ==========*/
    rc = MPI_Init(NULL, NULL);
    if (rc != MPI_SUCCESS) {
        printf ("Error starting MPI program. Terminating.\n");
        MPI_Abort(MPI_COMM_WORLD, rc);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if(rank == 0)
    {
        w = malloc(sizeof(int));
        h = malloc(sizeof(int));

        /* Read jpeg file */
        image = read_JPEG_file(argv[1], h, w);
        width = *w; free(w);
        height = *h; free(h);

        chunk_size = width * height * 3 / numtasks;

        /* Start timing */
        gettimeofday(&start,0);
    }

    MPI_Bcast(&chunk_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    image_chunk = (uint8_t*)malloc(chunk_size*sizeof(uint8_t));

    /* Facem scatter la imaginea initiala catre toate procesele */
    MPI_Scatter(image, chunk_size, MPI_CHAR, image_chunk, chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    /* Compute RGB->HSV */
    for (i = 0; i < chunk_size; i+=3) {
        RGBtoHSV(image_chunk + i);
    }

    /* Facem gather la datele calculate */
    MPI_Gather(image_chunk, chunk_size, MPI_CHAR, image, chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        /* End timing*/
        gettimeofday(&finish,0);

        /* Print result */
        t= (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec)
        / 1000000.0;
        printf("Time elapsed %lf\n", t);

        /* Write new jpeg file */
        write_JPEG_file (argv[2], 90, image, width, height);

        printf("MPI terminated successfully \n");
    }

    MPI_Finalize();
	return 0;
}