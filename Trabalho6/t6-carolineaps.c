//Caroline Aparecida RA 726506

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int floydWarshall(double **taxasConversao, int n);

int main() {

	int n, i, j;
	double **taxasConversao, taxa;

	while(1) {

		scanf("%d", &n);
		
		if (n == 0) {
			return 0;
		}
			
		taxasConversao = (double **)malloc(n * sizeof(double *));
	
		for (i = 0; i < n; i++) {
			taxasConversao[i] = (double *)malloc(n * sizeof(double));
		}	
	
	
		for (i = 0, taxa = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				scanf("%lf", &taxa);
				taxasConversao[i][j] = taxa;
			}
		}
	
		if (floydWarshall(taxasConversao, n)) {
			printf("S\n");
		} else {
			printf("N\n");
		}

		for (i = 0; i < n; i++) {
			free(taxasConversao[i]);
		}

		free(taxasConversao);

	}
	
	return 0;
}

int floydWarshall(double **taxasConversao, int n) {

	int k, i, j;

	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (taxasConversao[i][j] < taxasConversao[i][k]*taxasConversao[k][j]) {
					taxasConversao[i][j] = taxasConversao[i][k]*taxasConversao[k][j];
					if (i == j) {
						return 1;
					}
				}
			}
		}
	}

	return 0;

}

