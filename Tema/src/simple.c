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

int main(int argc, char **argv){
	/*==========  Variabile declarate  ==========*/
	struct timeval start,finish;
    double t;
    uint8_t* image;
    int *width,*height;
	/*-----  End of Variabile declarate  ------*/
    width = malloc(sizeof(int));
    height = malloc(sizeof(int));

	/* Read jpeg file */
    image = read_JPEG_file(argv[1], height, width);
    printf("Dupa fucntie %d %d\n", *width, *height);

	gettimeofday(&start,0);


    /* TODO - compute RGB->HSV */


    gettimeofday(&finish,0);

    t= (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec)
    / 1000000.0;
  	printf("Time elapsed %lf\n", t);

	/* Write new jpeg file */


	printf("Simple terminated successfully \n");
	return 0;
}