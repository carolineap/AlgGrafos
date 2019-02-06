//Caroline Aparecida RA 726506

#include <stdio.h>
#include <stdlib.h>

#define INFINITO 20000

typedef struct n {
	int indice;
	int custo;
	struct n *prox;
} No;

typedef struct f {
	No *vertice;
	No *inicio;
	No *fim;
} Fila;

typedef struct v {
	int estado;
	Fila *adj;
} Vertice;

typedef struct c {
	int distancia;
	int indice;
} Caminho;

void inicializaVertices(int n, int k, Vertice *vertices);
void insere_fila(Fila *fila, int indice, int custo);
void inicalizaFila(Fila *fila);
int *dijkstra(int n, int k, Vertice *vertices);
int menor_distancia(int *distancia, Vertice *vertices, int n);

int main() {

	int n, m, k, v, w, c;
	int i, menor_custo = 20000, custo = 0, indice = -1;
	Vertice *vertices;
	No *p;
	int *estufas_proximas;

	scanf("%d %d %d", &n, &m, &k);

	vertices = (Vertice *)malloc(n * sizeof(Vertice));

	inicializaVertices(n, k, vertices);

	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &v, &w, &c);
		insere_fila(vertices[v].adj, w, c);
		insere_fila(vertices[w].adj, v, c);
	}

	estufas_proximas = dijkstra(n, k, vertices);

	for (i = k; i < n; i++) {
		if (i + 1 < n) {
			printf("%d ", estufas_proximas[i]);
		} else {
			printf("%d\n", estufas_proximas[i]);
		}
	}

	return 0;
}


void inicializaVertices(int n, int k, Vertice *vertices) {
	int i;

	for (i = 0; i < n; i++) {
		vertices[i].estado = 1;
		vertices[i].adj = (Fila *)malloc(sizeof(Fila));
		inicalizaFila(vertices[i].adj);
	}
}

void inicalizaFila(Fila *fila) {
	fila->inicio = fila->fim = NULL;
}

void insere_fila(Fila *fila, int indice, int custo) {

	No *novo = (No *)malloc(sizeof(No));

	novo->custo = custo;
	novo->indice = indice;
	novo->prox = NULL;
	
	if (fila->inicio == NULL) {
		fila->inicio = novo;
		fila->fim = novo;
	} else {
		fila->fim->prox = novo;
		fila->fim = novo;
	}
}

int *dijkstra(int n, int k, Vertice *vertices) {
	
	int *estufas_proximas = (int *)malloc( n * sizeof(int));
	int *distancia = (int *)malloc( n * sizeof(int));
	int i, indice = 0;
	No *p;

	for (i = 0; i < n; i++) {
		if (i < k) {
			distancia[i] = 0; //estufas serão sempre removidas primeiro no laço principal
		} else {
			distancia[i] = INFINITO;
		}
		estufas_proximas[i] = -1; //inicializa vetor que guardará índice das estufas mais próximas
	}


 	i = 0;
	while (i < n) {

		indice = menor_distancia(distancia, vertices, n); //remove vértice com menor valor em distância
		vertices[indice].estado = 0; //para indicar que vértice não pode ser mais removido

		if (indice < k) {
			estufas_proximas[indice] = indice; //se é estufa, a estufa mais próxima é si mesma
		}

		i++;

		for (p = vertices[indice].adj->inicio; p != NULL; p = p->prox) {
			if (vertices[p->indice].estado && (distancia[p->indice] > distancia[indice] + p->custo)) {
				distancia[p->indice] = distancia[indice] + p->custo; //troca por distância menor
				estufas_proximas[p->indice] = estufas_proximas[indice]; //estufa mais próxima é a estufa que "originou a busca"
			} else if (vertices[p->indice].estado && (distancia[p->indice] == distancia[indice] + p->custo)) { 
				if (estufas_proximas[p->indice] > estufas_proximas[indice]) { //caso tenha achado índice menor com mesma distância
					estufas_proximas[p->indice] = estufas_proximas[indice];
				}
			}
		}
		
	};

	return estufas_proximas;

}

int menor_distancia(int *distancia, Vertice *vertices, int n) {

	int min = INFINITO, i, indice;

	for (i = 0; i < n; i++) {
		if (vertices[i].estado && min > distancia[i]) {
			min = distancia[i];
			indice = i;
		}
	}

	return indice;

}