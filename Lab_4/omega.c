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
	printf("Numar conexiuni = ");
	scanf("%hd", &conexiuni);

	short in[conexiuni], out[conexiuni];

	for (i = 0; i < conexiuni; ++i)
	{
		printf("In_%d = ", i+1);
		scanf("%hd", &in[i]);
		printf("Out_%d = ", i+1);
		scanf("%hd", &out[i]);
	}



	short etaje = log((double)intrari) / log(2.0);
	short mat[intrari][etaje+1];
	memset(mat, 0, sizeof(short) * intrari * (etaje+1));
	int j;

	printf("Etaje %hu\n", etaje);
	printf("Rezolvare \n");

	j = 0;
	while(j < conexiuni){
		short xor_tag = in[j] ^ out[j];

		printf("\n - Din %hu in %hu - \n", in[j], out[j]);

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
		if(mat[in[j]][0])
		{
			printf("Conflict\n");
		}
		else
		{

			printf("Mat[%d][%d] = %d\n", in[j], 0, mat[in[j]][i+1]);
			mat[in[j]][0] = 1;

			for(i = 0;  i < etaje; i++)
			{
				/* Verific bitul coresp stage-ului */
				aux = xor_tag & (1 << (etaje-i-1));

				printf("Comutatorul de pe etaj %hd - ", etaje-i-1);

				/* Direct */
				if (aux == 0)
				{
					/* Unde trebuie sa rutez mai departe */
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
					if(mat[in[j]][i+1])
					{
						printf("Conflict\n");
						break;
					}
					else
					{
						mat[in[j]][i+1] = 1;
						printf("Direct (C0 = 0; C1 = 0)\n");
					}

				}
				/* Cross */
				else
				{
					/* Este cross deci se modifica cu +1 sau -1 */
					if (in[j] % 2 == 0)
						++in[j];
					else
						--in[j];

					/* Unde trebuie sa rutez mai departe */
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
					if(mat[in[j]][i+1])
					{
						printf("Conflict\n");
						break;
					}
					else
					{
						mat[in[j]][i+1] = 1;
						printf("Invers (C0 = 1; C1 = 1)\n");
					}
				}
			}
		}
		j++;
	}
	return 0;
}

