#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 3
#define CHUNKSIZE 1

int main(){
  long a[N][N], b[N][N], c[N][N], v[N][N][N];
  int i,j,k,chunk,tid;
  omp_set_num_threads(N*N*N);

  /* Init matrix */
  for (i = 0; i < N ; i++){
    for ( j = 0; j < N; j++)
    {
      a[i][j] = b[i][j] = N*i+j;
    }
  }
  chunk  =  CHUNKSIZE;

  #pragma omp parallel
  {
    int nthreads = omp_get_num_threads();
    tid = omp_get_thread_num();
    if(tid == 0)
      printf("Threaduri la inceput: %d\n", nthreads);
  }

  /* Multiply stuff */
  #pragma omp parallel for shared(a,b,c,chunk) private(i,tid) schedule(static,chunk)
  for (i = 0; i < N; ++i)
  {
    #pragma omp parallel for shared(a,b,c,chunk,i) private(j,tid) schedule(static,chunk)
    for (j = 0; j < N; ++j)
    {
      c[i][j] = 0;
      #pragma omp parallel for shared(a,b,c,chunk,i,j) private(k,tid) schedule(static,chunk)
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
      printf("%ld\t",a[i][j]);
    }
    printf("\n");
  } 
  printf("\n");

    /* Print matrix */
  for (i = 0; i < N ; i++){
    for ( j = 0; j < N; ++j)
    {
      printf("%ld\t",b[i][j]);
    }
    printf("\n");
  } 
  printf("\n");

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
