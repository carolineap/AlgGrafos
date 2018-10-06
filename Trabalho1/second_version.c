#include <stdio.h>
#include <stdlib.h>
/* verifica se o grafo e bipartido tentando colorir com duas cores */

int verifica_bip(int u, int v, char *alunos);

int main() {

	int n, m; //numeros de alunos e pares
	int u, v; //pares de alunos que estao em angulo de ataque
	char *alunos; //vetor que representa os alunos (vertices)
	int i, resultado; 

	while(1) {
		
		scanf("%d %d", &n, &m);
		
		if (n == 0 && m == 0) 
			return 0;
		
		alunos = (char *)malloc(n*sizeof(char));

		for (i = 0; i < n; i++) 
			alunos[i] = '0'; //inicializacao
		

		for (i = 0, resultado = 1; i < m; i++) {
			scanf("%d %d", &u, &v);
			resultado = resultado * verifica_bip(u-1, v-1, alunos);
		}

		if (resultado) 
			printf("SIM\n");
		else 
			printf("NAO\n");

		free(alunos);

	}

	return 0;
}

int verifica_bip(int u, int v, char *alunos) {

	if ((alunos[u] != '0' && alunos[v] != '0') && (alunos[u] == alunos[v])) //vertices ja foram coloridos com cores iguais
		return 0;
	

	if (alunos[u] == '0' && alunos[v] == '0') { // vertices nao foram coloridos ainda
		alunos[u] = '1';
		alunos[v] = '2';
	} else if (alunos[v] == '0' && alunos[u] != '0') { //apenas um dos vertices foram coloridos
		if (alunos[u] == '1')
			alunos[v] = '2';
		else 
			alunos[v] = '1';
	} else if (alunos[u] == '0' && alunos[v] != '0') {  //apenas um dos vertices foram coloridos
		if (alunos[v] == '1')
			alunos[u] = '2';
		else 
			alunos[u] = '1';
	}	
		
	return 1;
}