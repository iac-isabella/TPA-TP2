# include <iostream>
# include <cmath>
# include <queue>
# include "ManipulaVetorBinario.h"
# include "csparse.h"
using namespace std;

cs* geraMatrizAtivacao(int** matrizAtivacao, cs* matrizTransicoes, int totalAcoes){

	// Fila de candidatos
	queue<int> filaCandidatos;
	filaCandidatos.push(1);

	// Cria os vetores
	bool* vetorEstadoInicial = criaVetorBinario(totalAcoes);
	bool* vetorTemporario = criaVetorBinario(totalAcoes);
	bool* vetorEstadoCandidato = criaVetorBinario(totalAcoes);

	do{
		// Recebe o primeiro elemento da fila de candidatos
		int estadoInicial = filaCandidatos.front();
		// Vetor do estado inicial recebe o binário do estado inicial
		vetorEstadoInicial = numero2VetorBinario(estadoInicial - 1, totalAcoes, vetorEstadoInicial);
		// Primeiro elemento da fila de candidatos é removido
		filaCandidatos.pop();
		// Gera os estados candidatos
		int indice = 1;

		while (indice <= totalAcoes){
			vetorTemporario = inserePosVetorBinario(indice, totalAcoes, vetorTemporario);
			vetorEstadoCandidato = geraEstadoAtvCandidato(vetorEstadoInicial, vetorTemporario, totalAcoes, vetorEstadoCandidato);

			// Se o vetor não se encontra vazio
			if (!verificaVetorVazio(vetorEstadoCandidato, totalAcoes)){
				// Se satisfaz todas as dependências
				if (verificaEstadoValido(vetorEstadoCandidato, vetorTemporario, matrizAtivacao, totalAcoes)){
					// Gera o estado inicial e o estado candidato
					int estadoCandidato = (int)pow(2, indice - 1) + estadoInicial;
					// Se o estado candidato tiver todas as tarefas realizadas, não existe motivo para inserir ele novamente na fila
					if (estadoCandidato < pow(2, totalAcoes) - 1){
						filaCandidatos.push(estadoCandidato);
					}
					// Cria nó
					updateEntry(matrizTransicoes, estadoInicial, estadoCandidato, 1);
				}
			}
			indice++;
		}

	} while (!filaCandidatos.empty());

	// Apaga os vetores
	deletaVetorBinario(vetorEstadoInicial);
	deletaVetorBinario(vetorTemporario);
	deletaVetorBinario(vetorEstadoCandidato);
	return matrizTransicoes;
}

cs* geraMatrizAtivacao(int** matrizAtivacao, int totalAcoes){
	// Inicia a Matriz de Transicoes vazia
	cs* matrizTransicoes = cs_spalloc(0, 0, 0, 1, 1);
	matrizTransicoes = geraMatrizAtivacao(matrizAtivacao, matrizTransicoes, totalAcoes);
	return matrizTransicoes;
}

cs* geraMatrizDesativacao(int** matrizDesativacao, cs* matrizTransicoes, int totalAcoes){

	// Fila de candidatos
	queue<int> filaCandidatos;
	filaCandidatos.push((int) pow(2, totalAcoes));

	// Cria os vetores
	bool* vetorEstadoInicial = criaVetorBinario(totalAcoes);
	bool* vetorTemporario = criaVetorBinario(totalAcoes);
	bool* vetorEstadoCandidato = criaVetorBinario(totalAcoes);

	do{
		// Recebe o primeiro elemento da fila de candidatos
		int estadoInicial = filaCandidatos.front();
		// Vetor do estado inicial recebe o binário do estado inicial
		vetorEstadoInicial = numero2VetorBinario(estadoInicial - 1, totalAcoes, vetorEstadoInicial);
		// Primeiro elemento da fila de candidatos é removido
		filaCandidatos.pop();
		// Gera os estados candidatos
		int indice = 1;

		while (indice <= totalAcoes){
			vetorTemporario = inserePosVetorBinario(indice, totalAcoes, vetorTemporario);
			vetorEstadoCandidato = geraEstadoDesCandidato(vetorEstadoInicial, vetorTemporario, totalAcoes, vetorEstadoCandidato);

			// Se o vetor não se encontra cheio
			if (!verificaVetorCheio(vetorEstadoCandidato, totalAcoes)){
				// Se satisfaz todas as dependências
				if (verificaEstadoValido(vetorEstadoInicial, vetorTemporario, matrizDesativacao, totalAcoes)){
					// Gera o estado inicial e o estado candidato
					int estadoCandidato = estadoInicial - (int) pow(2, indice - 1);
					// Se o estado candidato tiver todas as tarefas realizadas, não existe motivo para inserir ele novamente na fila
					if (estadoCandidato < pow(2, totalAcoes) - 1){
						filaCandidatos.push(estadoCandidato);
					}
					// Cria nó
					updateEntry(matrizTransicoes, estadoInicial, estadoCandidato, 1);
				}
			}
			indice++;
		}

	} while (!filaCandidatos.empty());

	// Apaga os vetores
	deletaVetorBinario(vetorEstadoInicial);
	deletaVetorBinario(vetorTemporario);
	deletaVetorBinario(vetorEstadoCandidato);
	return matrizTransicoes;
}

cs* geraMatrizDesativacao(int** matrizDesativacao, int totalAcoes){
	// Inicia a Matriz de Transicoes vazia
	cs* matrizTransicoes = cs_spalloc(0, 0, 0, 1, 1);
	matrizTransicoes = geraMatrizDesativacao(matrizDesativacao, matrizTransicoes, totalAcoes);
	return matrizTransicoes;
}

cs* geraMatrizTransicoes(int** matrizAtivacao, int** matrizDesativacao, int totalAcoes){
	cs* matrizTransicoes;
	// Gera a Matriz de Transicoes a partir da matriz de ativação
	matrizTransicoes = geraMatrizAtivacao(matrizAtivacao, totalAcoes);
	// Gera a Matriz de Transicoes a partir da matriz de desativação
	matrizTransicoes = geraMatrizDesativacao(matrizDesativacao, matrizTransicoes, totalAcoes);
	return matrizTransicoes;
}