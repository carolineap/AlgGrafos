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
	int cor;
	Fila *adj;
} Vertice;

void insere_fila(Fila *fila, int indice);
int remove_fila(Fila *fila);
int verifica_bipartido(Fila *fila, Vertice *alunos, int n);

int main () {
	int n, m;
	int i, u, v, rem;
	No *a;

	Vertice *alunos;
	Fila *fila = (Fila *)malloc(sizeof(Fila));
	fila->inicio = fila->fim = NULL;
	fila->tamanho = 0;

	while (1) {

		scanf("%d %d", &n, &m);

		if (n == 0 && m == 0)
			return 0;

		alunos = (Vertice *)malloc(n * sizeof(Vertice));
		for (i = 0; i < n; i++) {
			alunos[i].adj = (Fila *)malloc(sizeof(Fila));
			alunos[i].adj->tamanho = 0;
			alunos[i].adj->inicio = alunos[i].adj->fim = NULL;
			alunos[i].cor = 0;
		}

		for (i = 0; i < m; i++) {
			scanf("%d %d", &u, &v);
			insere_fila(alunos[u-1].adj, v - 1);
			insere_fila(alunos[v-1].adj, u - 1);
		}


		if (verifica_bipartido(fila, alunos, n)) 
			printf("SIM\n");
		else
			printf("NAO\n");

		for (i = 0; i < n; i++) {
			while(alunos[i].adj->tamanho) {
				remove_fila(alunos[i].adj);
			}
			free(alunos[i].adj);
		}

		free(alunos);

		while(fila->tamanho) 
			remove_fila(fila);

		fila->inicio = fila->fim = NULL;
		fila->tamanho = 0;
	}
	
	return 0;

}

int verifica_bipartido(Fila *fila, Vertice *alunos, int n) {

	No *a;
	int i, rem;

	for (i = 0; i < n; i++) {
		if (alunos[i].cor == 0)	{
			insere_fila(fila, i);
			alunos[i].cor = 1;
			while (fila->tamanho) {
				rem = remove_fila(fila);
				for (a = alunos[rem].adj->inicio; a != NULL; a = a->prox) {	
					if (alunos[a->indice].cor == 0) {
						alunos[a->indice].cor = alunos[rem].cor%2 + 1;
						insere_fila(fila, a->indice);	
					} else if (alunos[a->indice].cor == alunos[rem].cor) {
						return 0;
					} 						
				} 
			}
		}
	}

	return 1;
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