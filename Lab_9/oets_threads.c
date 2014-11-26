#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#define N 10
typedef struct str_thdata
{
    pthread_t* threads;
    int v[N];
} thdata;
void *pthread_function(void* data){
	int i;
	int aux, boss;
	thdata* data1 = (thdata*) data;
	// printf("%d\n", data1->v[0]);
	for (i = 0; i < N; ++i)
	{
		if(data1->threads[i] == pthread_self()){
			boss = i;
		}
	}
	if(data1->v[boss] > data1->v[boss + 1]){
		aux = data1->v[boss];
		data1->v[boss] = data1->v[boss + 1];
		data1->v[boss + 1] = aux;
	}
	// printf("Thread id %d\n", getpid());
	return NULL;
}

int main(int argc, char argv[]) {
	srand(42);
	thdata data1;
	int v[N];
	int i, j ,pas;
	int sorted = 0;
	int aux;

	for(i = 0; i < N; i++) {
		data1.v[i] = rand() % N;
	}

	for(i = 0; i < N; i++) {
		printf("%i\t", data1.v[i]);
	}
	printf("\n");

	pthread_t* threads;

	int n_threads = N;
	threads = (pthread_t*)malloc(n_threads * sizeof(pthread_t));
	data1.threads = threads;



	for ( pas = 1; pas <= N; pas++){
		for(j = pas % 2; j < N - 1; j += 2){
			pthread_create(threads + j, NULL, &pthread_function, &data1);
		}
	}

    for (i = 0; i < n_threads; i++){
        pthread_join(threads[i], NULL);
    }


	for(i = 0; i < N; i++) {
		printf("%i\t", data1.v[i]);
	}
	printf("\n");
}