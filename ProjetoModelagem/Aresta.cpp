/*
Autores:
        Isabella de Albuquerque
        Thanner Soares
Trabalho pratico 2
Biblioteca de Arestas
*/

#include <stdio.h>
#include "Aresta.h"

/* Funcao para criar uma Aresta. */
Aresta criar(int origem, int destino){
	
	Aresta aresta;
	aresta.origem = origem;
	aresta.destino = destino;
	return aresta;

}

/* Funcao para excluir uma Aresta. */
void excluir(Aresta* Aresta){
	
	free(Aresta);

}

/* Funcao para alterar os dados de uma Aresta. */
void alterar(Aresta* Aresta, char origem, char destino){
	
	Aresta->origem = origem;
	Aresta->destino = destino;
	
}

/* Funcao para exibir os dados da Aresta no formato origem -> destino. */
char* to_string(Aresta* Aresta){
	char resultado[7];
	resultado[0] = Aresta->origem;
	resultado[1] = ' ';
	resultado[2] = '-';
	resultado[3] = '>';
	resultado[4] = ' ';
	resultado[5] = Aresta->destino;
	resultado[6] = '\0';

}