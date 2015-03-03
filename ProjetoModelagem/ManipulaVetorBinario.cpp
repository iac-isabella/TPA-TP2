#include <iostream>
#include "ManipulaVetorBinario.h"
#include "csparse.h"
using namespace std;

bool* criaVetorBinario(int tamanhoVetor){
	bool* vetor = new bool[tamanhoVetor];
	return vetor;
}

bool* numero2VetorBinario(int numero, int tamanhoVetor, bool* vetor){
	int indiceVetor = 0;
	// Bloco responsável por gerar o vetor dado o número
	while (numero > 0){
		if (numero % 2 == 0)
			vetor[indiceVetor] = 0;
		else
			vetor[indiceVetor] = 1;
		numero /= 2;
		indiceVetor++;
	}
	// Bloco responsável por considerar o restante do vetor que não foi avaliado pelo número como 0
	for (indiceVetor; indiceVetor < tamanhoVetor; indiceVetor++)
		vetor[indiceVetor] = 0;
	// Retorna o vetor
	return vetor;
}

bool* inserePosVetorBinario(int indice, int tamanhoVetor, bool* vetor){
	int indiceVetor = 0;
	while (indiceVetor < tamanhoVetor){
		if (indiceVetor == indice - 1)
			vetor[indiceVetor] = 1;
		else
			vetor[indiceVetor] = 0;
		indiceVetor++;
	}
	// Retorna o vetor
	return vetor;
}

bool* geraEstadoAtvCandidato(bool* vetorEstadoInicial, bool* vetorTemporario, int tamanhoVetor, bool* vetorEstadoCandidato){
	int indiceVetor;
	for (indiceVetor = 0; indiceVetor < tamanhoVetor; indiceVetor++){
		// Se está tentando executar uma tarefa que já se encontra executada
		if (vetorEstadoInicial[indiceVetor] == 1 && vetorTemporario[indiceVetor] == 1)
			return limpaVetorBinario(vetorEstadoCandidato, tamanhoVetor);
		else
			vetorEstadoCandidato[indiceVetor] = vetorEstadoInicial[indiceVetor] | vetorTemporario[indiceVetor];
	}
	return vetorEstadoCandidato;
}

bool* geraEstadoDesCandidato(bool* vetorEstadoInicial, bool* vetorTemporario, int tamanhoVetor, bool* vetorEstadoCandidato){
	int indiceVetor;
	for (indiceVetor = 0; indiceVetor < tamanhoVetor; indiceVetor++){
		// Se está tentando executar uma tarefa que já se encontra executada
		if (vetorEstadoInicial[indiceVetor] == 0 && vetorTemporario[indiceVetor] == 1)
			return completaVetorBinario(vetorEstadoCandidato, tamanhoVetor);
		else if (vetorEstadoInicial[indiceVetor] == 1 && vetorTemporario[indiceVetor] == 0)
			vetorEstadoCandidato[indiceVetor] = 1;
		else
			vetorEstadoCandidato[indiceVetor] = 0;
	}
	return vetorEstadoCandidato;
}

bool* limpaVetorBinario(bool* vetorEstadoCandidato, int tamanhoVetor){
	for (int indiceVetor = 0; indiceVetor < tamanhoVetor;indiceVetor++)
		vetorEstadoCandidato[indiceVetor] = 0;
	return vetorEstadoCandidato;
}

bool* completaVetorBinario(bool* vetorEstadoCandidato, int tamanhoVetor){
	for (int indiceVetor = 0; indiceVetor < tamanhoVetor; indiceVetor++)
		vetorEstadoCandidato[indiceVetor] = 1;
	return vetorEstadoCandidato;
}

bool verificaVetorVazio(bool* vetorEstadoCandidato, int tamanhoVetor){
	int indiceVetor = 0;
	while (indiceVetor < tamanhoVetor){
		if (vetorEstadoCandidato[indiceVetor] != 0)
			return false;
		indiceVetor++;
	}
	return true;
}

bool verificaVetorCheio(bool* vetorEstadoCandidato, int tamanhoVetor){
	int indiceVetor = 0;
	while (indiceVetor < tamanhoVetor){
		if (vetorEstadoCandidato[indiceVetor] != 1)
			return false;
		indiceVetor++;
	}
	return true;
}

bool verificaEstadoValido(bool* vetorEstadoCandidato, bool* vetorTemporario, int** matrizRestricao, int tamanhoVetor){
	int indiceVetor = 0;
	bool estadoCandidatoValido = true;
	// Enquanto não percorrer todas as tarefas e o estado candidato continuar válido
	while (indiceVetor < tamanhoVetor && estadoCandidatoValido){
		// Se tiver ocorrido a transição de uma tarefa 
		if (vetorTemporario[indiceVetor] == 1){
			// Verifica se existe alguma dependência que está sendo descumprida
			for (int coluna = 0; coluna < tamanhoVetor; coluna++){
				// Se a matriz tiver a dependência e o estado candidato não satisfazer a dependência
				if (matrizRestricao[indiceVetor][coluna] == 1 && vetorEstadoCandidato[coluna] == 0)
					estadoCandidatoValido = false;
			}
		}
		indiceVetor++;
	}
	return estadoCandidatoValido;
}

void imprimeVetorBinario(bool* vetor, int tamanhoVetor){
	for (int indiceVetor = tamanhoVetor - 1; indiceVetor >= 0; indiceVetor--)
		cout << vetor[indiceVetor] << " ";
	cout << "\n";
}

void imprimeVetorInteiro(int* vetor, int tamanhoVetor){
	for (int indiceVetor = tamanhoVetor - 1; indiceVetor >= 0; indiceVetor--)
		cout << vetor[indiceVetor] << " ";
	cout << "\n";
}

void deletaVetorBinario(bool* vetor){
	delete(vetor);
}