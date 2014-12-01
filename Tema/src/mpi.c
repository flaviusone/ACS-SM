/**
*
* Author: Flavius Tirnacop
* Grupa: 341C1
* Fisier: simple.c
* Descriere: Implementare seriala transformare RGB->HSV
*
**/

/*==========  Includes & Defines  ==========*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <jpeglib.h>
#include <math.h>
#include <sys/time.h>
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
    double t;
    uint8_t* image;
    int *width,*height;
    int i;
	/*-----  End of Variabile declarate  ------*/
    width = malloc(sizeof(int));
    height = malloc(sizeof(int));

	/* Read jpeg file */
    image = read_JPEG_file(argv[1], height, width);

    /* Start timing */
	gettimeofday(&start,0);


    /* Compute RGB->HSV */
    for (i = 0; i < *width * *height; i++) {
        RGBtoHSV(image + i * 3);
    }


	/* End timing*/
    gettimeofday(&finish,0);

    /* Print result */
    t= (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec)
    / 1000000.0;
  	printf("Time elapsed %lf\n", t);

	/* Write new jpeg file */
	write_JPEG_file (argv[2], 90, image, *width, *height);


	printf("Simple terminated successfully \n");
	return 0;
}