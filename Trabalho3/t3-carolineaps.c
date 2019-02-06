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
	int f;
	Fila *adj;
	Fila *adjT;
} Vertice;

void inicializaVertices(int n, Vertice *rua);
void insere_fila(Fila *fila, int indice);
int remove_fila(Fila *fila);
void inicalizaFila(Fila *fila);
void dfs_aux(Vertice *rua, Vertice *u, int *tempo, int flag);
int dfs(Vertice *rua, int n);

int main() {

	int n, m;
	int v, w, p;
	int i;
	No *u;

	Vertice *rua;

	while (1) {

		scanf("%d %d", &n, &m);

		if (n == 0 && m == 0)
			return 0;

		rua = (Vertice *)malloc(n * sizeof(Vertice));

		for (i = 0; i < n; i++) { 
			rua[i].adj = (Fila *)malloc(sizeof(Fila));
			rua[i].adjT = (Fila *)malloc(sizeof(Fila));
			inicalizaFila(rua[i].adj);
			inicalizaFila(rua[i].adjT);
		}

		/* Guarda adjacencias do grafo original e transposto */
		for (i = 0; i < m; i++) {
			scanf("%d %d %d", &v, &w, &p);
			if (p == 1) {
				insere_fila(rua[v - 1].adj, w - 1);
				insere_fila(rua[w - 1].adjT, v - 1);
			} else {
				insere_fila(rua[v - 1].adj, w - 1);
				insere_fila(rua[w - 1].adj, v - 1);
				insere_fila(rua[v - 1].adjT, w - 1);
				insere_fila(rua[w - 1].adjT, v - 1);						
			}

		}

		/* Funcao dfs verifica se o grafo e uma componente fortemente conexa */
		printf("%d\n", dfs(rua, n));


		/* Libera listas */
		for (i = 0; i < n; i++) {
			while(rua[i].adj->tamanho) {
				remove_fila(rua[i].adj);
			}
			while(rua[i].adjT->tamanho){
				remove_fila(rua[i].adjT);
			}
			free(rua[i].adj);
		}

		free(rua);
	}

	return 0;
}

void inicializaVertices(int n, Vertice *rua) {

	int i;

	for (i = 0; i < n; i++) {
		rua[i].cor = 0;
		rua[i].f = 0;
	}
}

void inicalizaFila(Fila *fila) {
	fila->inicio = fila->fim = NULL;
	fila->tamanho = 0;
}

int dfs(Vertice *rua, int n) {

	int i;
	int tempo;
	int max;

	/* Faz busca no grafo original a partir do vertice 0*/
	tempo = 0;
	inicializaVertices(n, rua);
	dfs_aux(rua, &rua[0], &tempo, 1);
	
	/* Se a partir do vertice 0 nao chegar em todos os outros, ja nao e CFC */
	/* Acha vertice com maior f */
	max = 0;
	for (i = 1; i < n; i++) {
		if (rua[i].cor == 0) return 0;
		if (rua[i].f > rua[max].f) 
			max = i;
	}

	/* Faz busca no grafo transposto a partir do vertice de maior f */
	tempo = 0;
	inicializaVertices(n, rua);
	dfs_aux(rua, &rua[max], &tempo, 0);

	/* Se nao chegou em todos os outros, nao e CFC */
	for (i = 0; i < n; i++) {
		if (rua[i].cor == 0) return 0;
	}

	return 1;
}


void dfs_aux(Vertice *rua, Vertice *u, int *tempo, int flag) {
	No *v;

	*tempo = *tempo + 1;

	u->cor = 1;

	//flag verifica se a dfs sera no grafo original ou no grafo transposto
	if (flag)
		v = u->adj->inicio;
	else 
		v = u->adjT->inicio; 

	for (; v != NULL; v = v->prox) {
		if (rua[v->indice].cor == 0) {
			dfs_aux(rua, &rua[v->indice], tempo, flag);
		}
	}

	u->f = *tempo;
	*tempo = *tempo + 1;

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