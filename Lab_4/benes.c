#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[])
{
	short intrari, conexiuni;
	int i;
	int aux;

	printf("Numar intrari = ");
	scanf("%hd", &intrari);
	// printf("Numar conexiuni = ");
	// scanf("%hd", &conexiuni);
	conexiuni = 1;

	short in[conexiuni], out[conexiuni];

	for (i = 0; i < conexiuni; ++i)
	{
		printf("In_%d = ", i+1);
		scanf("%hd", &in[i]);
		printf("Out_%d = ", i+1);
		scanf("%hd", &out[i]);
	}



	short etaje =2 * (log((double)intrari) / log(2.0)) - 1;
	short mat[intrari][etaje+1];
	memset(mat, 0, sizeof(short) * intrari * (etaje+1));
	int j;

	printf("Etaje %hu\n", etaje);
	printf("Rezolvare \n");

	j = 0;
	while(j < conexiuni){
		short xor_tag = in[j] ^ out[j];

		printf("\n - Din %hu in %hu - \n", in[j], out[j]);

		printf("Direct (C0 = 0; C1 = 0)\n");
		printf("Direct (C0 = 0; C1 = 0)\n");

		/* Daca e < 4 atunci direct altfel cross */
		if (in[j] >= 4)
		{
			in[j] = in[j] << 1;
			in[j] = in[j] + 1;
			in[j] = in[j] & 7;
		}
		else
		{
			in[j] = in[j] << 1;
		}

		if(in[j] == 1) in[j]--;
		if(in[j] == 2) in[j]++;
		if(in[j] == 5) in[j]--;
		if(in[j] == 6) in[j]++;

		if(out[j]<4){
			if (in[j] % 2 == 0)
				printf("Direct (C0 = 0; C1 = 0)\n");
			else{
				printf("Invers (C0 = 1; C1 = 1)\n");
				if (in[j] % 2 == 0)
					++in[j];
				else
					--in[j];
			}
		}
		else
		{
			if (in[j] % 2 == 1)
				printf("Direct (C0 = 0; C1 = 0)\n");
			else{
				printf("Invers (C0 = 1; C1 = 1)\n");
				if (in[j] % 2 == 0)
					++in[j];
				else
					--in[j];
			}
		}

		/* Daca e < 4 atunci direct altfel cross */
		if (in[j] >= 4)
		{
			in[j] = in[j] << 1;
			in[j] = in[j] + 1;
			in[j] = in[j] & 7;
		}
		else
		{
			in[j] = in[j] << 1;
		}



		++j;
	}

	return 0;

}