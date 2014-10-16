#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define procs 33

int main(){

	double S_n, E_n, R_n, U_n, Q_n, T_n, O_1, T_1, O_n;

	int n;
	FILE* f;

	f = fopen("out", "w");

	for(n = 1 ; n < procs; n++){
		O_1 = pow(n, 3);
		T_1 = pow(n, 3);
		O_n = pow(n, 3) + pow(n, 2) * log2(n);
		T_n = (4 * pow(n, 3)) / (n+3);
		S_n = T_1 / T_n; 
		E_n = S_n / n;
		R_n = O_n / O_1;
		U_n = R_n * E_n;
		Q_n = S_n * E_n / R_n;
		fprintf(f, "%d\t%lf\t%lf\t%lf\t%lf\t%lf\n", n,S_n, E_n, R_n, U_n, Q_n);
	}

	fclose(f);	
}