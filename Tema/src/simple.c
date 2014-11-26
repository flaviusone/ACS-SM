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
#include <time.h>
// #include "jpeg_functions.h"
/*-----  End of Includes & Defines  ------*/

int main(int argc, char **argv){
	/*==========  Variabile declarate  ==========*/
	struct timeval start,finish;
    double t;
	/*-----  End of Variabile declarate  ------*/


	/* Read jpeg file */

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