/**
*
* Author: Flavius Tirnacop
* Grupa: 341C1
* Fisier: pthreads.c
* Descriere: Implementare seriala transformare RGB->HSV
*
**/

/*==========  Includes & Defines  ==========*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>
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

int thread_work;

void *thread_job(void *ptr)
{
    int j;
    uint8_t *image_chunk = (uint8_t*)ptr;
    for (j = 0; j < thread_work; j+=3)
    {
        RGBtoHSV(image_chunk + j);
    }
    return 0;
}

int main(int argc, char **argv){
	/*==========  Variabile declarate  ==========*/
	struct timeval start,finish;
    double t;
    uint8_t* image;
    int width,height;
    int *w,*h;
    int i, numthreads;
    pthread_t *threads;
	/*-----  End of Variabile declarate  ------*/

    /* Get number of threads */
    numthreads = atoi(argv[1]);

    w = malloc(sizeof(int));
    h = malloc(sizeof(int));

	/* Read jpeg file */
    image = read_JPEG_file(argv[2], h, w);
    width = *w; free(w);
    height = *h; free(h);

    /* Start timing */
	gettimeofday(&start,0);

    threads = (pthread_t*)malloc(numthreads * sizeof(pthread_t));
    thread_work = width * height * 3 / numthreads;

    /* Create Pthreads */
    for(i = 0; i < numthreads; i++){
        pthread_create( threads + i, NULL, thread_job, image+i*thread_work);
    }

    /* Join Pthreads */
    for (i = 0; i < numthreads; i++){
        pthread_join(threads[i], NULL);
    }

	/* End timing*/
    gettimeofday(&finish,0);

    /* Print result */
    t= (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec)
    / 1000000.0;
  	printf("Time elapsed %lf\n", t);

	/* Write new jpeg file */
	write_JPEG_file (argv[3], 90, image, width, height);


	printf("Pthreads terminated successfully \n");
	return 0;
}
