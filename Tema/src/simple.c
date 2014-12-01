/**
*
* Author: Flavius Tirnacop
* Grupa: 341C1
* Fisier: serial.c
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

#define EPSILON 0.02

static int minf(uint8_t a, uint8_t b, uint8_t c) {
    if ((a < b) && (a < c)) {
        return a;
    } else if ((b < a) && (b < c)) {
        return b;
    } else {
        return c;
    }
}

static int maxf(uint8_t a, uint8_t b, uint8_t c) {
    if ((a > b) && (a > c)) {
        return a;
    } else if ((b > a) && (b > c)) {
        return b;
    } else {
        return c;
    }
}


static void RGBtoHSV(uint8_t * src) {
    uint8_t min, max;
    float max2;
    float delta;
    float h;

    min = minf(src[0], src[1], src[2]);
    max = maxf(src[0], src[1], src[2]);

    max2 = max + EPSILON;

    delta = max2 - min;

    if (src[0] == max)
        h = (src[1] - src[2]) / delta;
    else if (src[1] == max)
        h = 2 + (src[2] - src[0]) / delta;
    else
        h = 4 + (src[0] - src[1]) / delta;

    h *= 60;
    if (h < 0)
        h += 360;

    src[0] = (h / 360.) * 255;
    src[1] = delta * 255 / max2;
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


    /* TODO - compute RGB->HSV */
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