# include <iostream>
# include <cmath>
# include <queue>
# include "ManipulaVetorBinario.h"
# include "matrizEsparsa.h"
using namespace std;

matrizEsparsa* geraMatrizSistema(matrizEsparsa* matrizRestricao){

	int numeroTarefas = 3;	
	
	// Inicia a matriz do sistema vazia
	matrizEsparsa* matrizSistema = geraMatrizEsparsa(8);

	// Fila de candidatos
	queue<int> filaCandidatos;
	filaCandidatos.push(0);

	// Cria os vetores
	bool* vetorEstadoInicial = criaVetorBinario(numeroTarefas);
	bool* vetorTemporario = criaVetorBinario(numeroTarefas);
	bool* vetorEstadoCandidato = criaVetorBinario(numeroTarefas);

	do{
		// Recebe o primeiro elemento da fila de candidatos
		int estadoInicial = filaCandidatos.front();
		// Vetor do estado inicial recebe o binário do estado inicial
		vetorEstadoInicial = numero2VetorBinario(estadoInicial,numeroTarefas,vetorEstadoInicial);
		// Primeiro elemento da fila de candidatos é removido
		filaCandidatos.pop();
		// Gera os estados candidatos
		int estado = 1;

		cout << "vetor estado inicial" << "\n";
		imprimeVetorBinario(vetorEstadoInicial, numeroTarefas);
		cout << "\n\n";

		while (estado < pow(2, numeroTarefas)){
			vetorTemporario = numero2VetorBinario(estado, numeroTarefas, vetorTemporario);
			vetorEstadoCandidato = geraEstadoCandidato(vetorEstadoInicial, vetorTemporario, numeroTarefas, vetorEstadoCandidato);

			cout << "vetor temporario" << "\n";
			imprimeVetorBinario(vetorTemporario, numeroTarefas);
			cout << "vetor estado candidato" << "\n";
			imprimeVetorBinario(vetorEstadoCandidato, numeroTarefas);
			
			// Se o vetor não se encontra vazio
			if (!verificaVetorVazio(vetorEstadoCandidato, numeroTarefas)){
				// Se satisfaz todas as dependências
				if (verificaDependencias(vetorEstadoCandidato, vetorTemporario, matrizRestricao, numeroTarefas)){
					cout << "aceitou" <<endl;
					// Gera o estado inicial e o estado candidato
					int estadoCandidato = estado + estadoInicial;
					// Se o estado candidato tiver todas as tarefas realizadas, não existe motivo para inserir ele novamente na fila
					if (estadoCandidato < pow(2, numeroTarefas) - 1){
						int x = 0;
						// filaCandidatos.push(estadoCandidato);
					}
					// Cria nó
					adicionaValor(matrizSistema, 1, estadoInicial + 1, estadoCandidato + 1);
				}
			}
			cout << endl;
			estado++;
		}

	} while (!filaCandidatos.empty());
	
	// Apaga os vetores
	deletaVetorBinario(vetorEstadoInicial);
	deletaVetorBinario(vetorTemporario);
	deletaVetorBinario(vetorEstadoCandidato);
	return matrizSistema;
}