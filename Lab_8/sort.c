#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100

int main(int argc, char argv[]) {
	srand(42);
	int v[N];
	int i, j ,pas;
	int sorted = 0;
	int aux;

	omp_set_num_threads(4);

	for(i = 0; i < N; i++) {
		v[i] = rand() % N;
	}

	#pragma omp parallel private(pas)
	{
		for ( pas = 1; pas <= N; pas++){
			#pragma omp for private(j, aux)
			for(j = pas % 2; j < N - 1; j += 2)
			{
				if(v[j] > v[j + 1]){
					aux = v[j];
					v[j] = v[j + 1];
					v[j + 1] = aux;
				}
			}
		}
	}
	for(i = 0; i < N; i++) {
		printf("%i\t", v[i]);
	}
	printf("\n");
}