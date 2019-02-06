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
	int depTempo;
	int tempo;
	int cor;
	int f;
	Fila *adj;
} Vertice;

void inicializaVertices(int n, Vertice *projeto);
void insere_fila(Fila *fila, int indice);
int remove_fila(Fila *fila);
void inicalizaFila(Fila *fila);
void dfs_aux(Vertice *projeto, int i, int *topSort, int *flag);
int dfs(Vertice *projeto, int n);

int main() {

	int n, m;
	int v, w;
	int i;
	No *u;

	Vertice *projeto;

	while (1) {

		scanf("%d %d", &n, &m);

		if (n == 0 && m == 0)
			return 0;

		projeto = (Vertice *)malloc(n * sizeof(Vertice));

		for (i = 0; i < n; i++) { 
			scanf("%d", &projeto[i].tempo);
			projeto[i].depTempo = 0;
			projeto[i].adj = (Fila *)malloc(sizeof(Fila));
			inicalizaFila(projeto[i].adj);
		}

		/* Guarda adjacencias do grafo */
		for (i = 0; i < m; i++) {
			scanf("%d %d", &v, &w);
			insere_fila(projeto[v].adj, w);
		}

		/* Funcao dfs realiza top sort e verifica qual tempo minimo necessario para realiza-las */
		printf("%d\n", dfs(projeto, n));


		/* Libera listas */
		for (i = 0; i < n; i++) {
			while(projeto[i].adj->tamanho) {
				remove_fila(projeto[i].adj);
			}
			free(projeto[i].adj);
		}

		free(projeto);
	}

	return 0;
}

void inicializaVertices(int n, Vertice *projeto) {

	int i;

	for (i = 0; i < n; i++) {
		projeto[i].cor = 0;
		projeto[i].f = 0;
	}
}

void inicalizaFila(Fila *fila) {
	fila->inicio = fila->fim = NULL;
	fila->tamanho = 0;
}

int dfs(Vertice *projeto, int n) {

	int i, max;
	int *topSort = (int *)malloc(n*sizeof(int));
	No *v;
	int f = n;

	inicializaVertices(n, projeto);
	for (i = 0; i < n; i++) {
		if (projeto[i].cor == 0) {
			dfs_aux(projeto, i, topSort, &f);
		}
	}

	max = 0;
	for (i = 0; i < n; i++) {
		for (v = projeto[topSort[i]].adj->inicio; v != NULL; v = v->prox) {
			if (projeto[topSort[i]].tempo + projeto[topSort[i]].depTempo > projeto[v->indice].depTempo) {
				projeto[v->indice].depTempo = projeto[topSort[i]].tempo + projeto[topSort[i]].depTempo;
			}
		}
		projeto[topSort[i]].depTempo = projeto[topSort[i]].depTempo + projeto[topSort[i]].tempo;
		if (projeto[topSort[i]].depTempo > max) 
			max = projeto[topSort[i]].depTempo;
	}

	free(topSort);

	return max;
}

void dfs_aux(Vertice *projeto, int i, int *topSort, int *flag) {
	No *v;
	Vertice *aux;

	projeto[i].cor = 1;

	for (v = projeto[i].adj->inicio; v != NULL; v = v->prox) {
		if (projeto[v->indice].cor == 0) {
			dfs_aux(projeto, v->indice, topSort, flag);
		}
	}

	*flag = *flag - 1;
	topSort[*flag] = i;

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