#include <stdio.h>
#include <stdlib.h>

#define N 3

int main(){
	long a[N][N], b[N][N], c[N][N];
	int i,j,k;

	/* Init matrix */
	for (i = 0; i < N ; i++){
		for ( j = 0; j < N; j++)
		{
			a[i][j] = b[i][j] = N*i+j;
		}
	}

	/* Multiply stuff */
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			c[i][j] = 0;
			for (k = 0; k < N; ++k)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	/* Print matrix */
	for (i = 0; i < N ; i++){
		for ( j = 0; j < N; ++j)
		{
			printf("%ld\t",c[i][j]);
		}
		printf("\n");
	}	

	return 0;
}
