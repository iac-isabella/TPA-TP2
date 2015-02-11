#include <iostream>
#include "ManipulaVetorBinario.h"
#include "matrizEsparsa.h"
using namespace std;

bool* criaVetorBinario(int tamanhoVetor){
	bool* vetor = new bool[tamanhoVetor];
	return vetor;
}

bool* numero2VetorBinario(int numero, int tamanhoVetor, bool* vetor){
	int indiceVetor = 0;
	// Bloco respons�vel por gerar o vetor dado o n�mero
	while (numero > 0){
		if (numero % 2 == 1)
			vetor[indiceVetor] = 1;
		else
			vetor[indiceVetor] = 0;
		numero /= 2;
		indiceVetor++;
	}
	// Bloco respons�vel por considerar o restante do vetor que n�o foi avaliado pelo n�mero como 0
	for (indiceVetor; indiceVetor < tamanhoVetor; indiceVetor++)
		vetor[indiceVetor] = 0;
	// Retorna o vetor
	return vetor;
}

bool* geraEstadoCandidato(bool* vetorEstadoInicial, bool* vetorTemporario, int tamanhoVetor, bool* vetorEstadoCandidato){
	int indiceVetor;
	for (indiceVetor = 0; indiceVetor < tamanhoVetor; indiceVetor++){
		// Se est� tentando executar uma tarefa que j� se encontra executada
		if (vetorEstadoInicial[indiceVetor] == 1 && vetorTemporario[indiceVetor] == 1)
			return limpaVetorBinario(vetorEstadoCandidato, tamanhoVetor);
		else
			vetorEstadoCandidato[indiceVetor] = vetorEstadoInicial[indiceVetor] | vetorTemporario[indiceVetor];
	}
	return vetorEstadoCandidato;
}

bool* limpaVetorBinario(bool* vetorEstadoCandidato, int tamanhoVetor){
	for (int indiceVetor = 0; indiceVetor < tamanhoVetor;indiceVetor++)
		vetorEstadoCandidato[indiceVetor] = 0;
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

bool verificaDependencias(bool* vetorEstadoCandidato, bool* vetorTemporario, matrizEsparsa* matriz, int tamanhoVetor){
	int indiceVetor = 0;
	bool estadoCandidatoValido = true;
	// Enquanto n�o percorrer todas as tarefas e o estado candidato continuar v�lido
	while (indiceVetor < tamanhoVetor && estadoCandidatoValido){
		// Se tiver ocorrido a transi��o de uma tarefa 
		if (vetorTemporario[indiceVetor] == 1){
			// Verifica, primeiramente, se a tarefa pode existir no fluxo
			if (!tarefaExisteFluxo(matriz, indiceVetor+1))
				estadoCandidatoValido = false;
			// Se existir no fluxo
			else{
				// Verifica se existe alguma depend�ncia que est� sendo descumprida
				for (int coluna = 0; coluna < tamanhoVetor; coluna++){
					// Se a matriz tiver a depend�ncia e o estado candidato n�o satisfazer a depend�ncia
					if (valorPosicao(matriz,indiceVetor,coluna) == 1 && vetorEstadoCandidato[coluna] == 0)
						estadoCandidatoValido = false;
				}
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