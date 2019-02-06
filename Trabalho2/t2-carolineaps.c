#include <stdio.h>
#include <stdlib.h>

typedef struct n {
	int indice;
	struct n *prox;
} No;

typedef struct f {
	int tamanho;
	No *vertice;
	No *inicio;
	No *fim;
} Fila;

typedef struct v {
	int distancia;
	Fila *adj;
} Vertice;

void insere_fila(Fila *fila, int indice);
int remove_fila(Fila *fila);
int verificaMenorCaminho(Fila *fila, Vertice *pessoas, int n);

int main () {
	int n, m;
	int i, u, v, rem, distancia;
	No *a;

	Vertice *pessoas;
	Fila *fila = (Fila *)malloc(sizeof(Fila));
	fila->inicio = fila->fim = NULL;
	fila->tamanho = 0;

	while (1) {

		scanf("%d %d", &n, &m);

		if (n == 0 && m == 0)
			return 0;

		pessoas = (Vertice *)malloc(n * sizeof(Vertice));

		for (i = 0; i < n; i++) {
			pessoas[i].adj = (Fila *)malloc(sizeof(Fila));
			pessoas[i].adj->tamanho = 0;
			pessoas[i].adj->inicio = pessoas[i].adj->fim = NULL;
			pessoas[i].distancia = -1;
		}

		for (i = 0; i < m; i++) {
			scanf("%d %d", &u, &v);
			insere_fila(pessoas[u].adj, v);
			insere_fila(pessoas[v].adj, u);
		}
	
		distancia = verificaMenorCaminho(fila, pessoas, n);

		if (distancia == -1) 
			printf("infinito\n");
		else
			printf("%d\n", distancia);

		for (i = 0; i < n; i++) {
			while(pessoas[i].adj->tamanho) {
				remove_fila(pessoas[i].adj);
			}
			free(pessoas[i].adj);
		}

		free(pessoas);

		while(fila->tamanho) 
			remove_fila(fila);

		fila->inicio = fila->fim = NULL;
		fila->tamanho = 0;
	}
	
	return 0;

}

int verificaMenorCaminho(Fila *fila, Vertice *pessoas, int n) {
	
	No *a;
	int i, rem, distancia = 0, max = -1;

	insere_fila(fila, 0);
	pessoas[0].distancia = 0;

	while (fila->tamanho) {
		rem = remove_fila(fila);
		for (a = pessoas[rem].adj->inicio; a != NULL; a = a->prox) {	
			if (pessoas[a->indice].distancia == -1) {
				pessoas[a->indice].distancia = pessoas[rem].distancia + 1;
				insere_fila(fila, a->indice);	
			} 					
		} 
	}
			
	for (i = 0; i < n; i++) {
		if (pessoas[i].distancia == -1) return -1;
		if (pessoas[i].distancia > max)
			max = pessoas[i].distancia; 
	}

	return max;
}

void insere_fila(Fila *fila, int indice) {

	No *novo = (No *)malloc(sizeof(No));

	novo->indice = indice;
	novo->prox = NULL;
	
	if (fila->inicio == NULL) {
		fila->inicio = novo;
		fila->fim = novo;
	} else {
		fila->fim->prox = novo;
		fila->fim = novo;
	}

	fila->tamanho++;
}

int remove_fila(Fila *fila) {

	No *rem = fila->inicio;
	int r = fila->inicio->indice;

	fila->inicio = fila->inicio->prox;
	fila->tamanho--;

	if(!fila->tamanho) {
		fila->fim = fila->inicio = NULL;
	} 

	free(rem);

	return r;
}