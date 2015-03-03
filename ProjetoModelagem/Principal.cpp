# include <iostream>
# include <queue>
#include <vector>
# include <string>
#include <fstream>
# include "ManipulaArquivo.h"
# include "ImprimeMatriz.h"
# include "MatrizTransicoes.h"
# include "csparse.h"
using namespace std;

// Definindo o total de acoes do modelo
# define totalAcoes 3

// Estrutura de dados que representa uma Aresta.
typedef struct {

	int origem;
	int destino;

} Aresta;

// Funcao para exibir os dados da Aresta no formato origem -> destino.
string to_string(Aresta aresta){

	string str = "";
	str += std::to_string(aresta.origem);
	str += " -> ";
	str += std::to_string(aresta.destino);
	str += ";";
	return str;

}

// Funcao para gerar um arquivo com as definições do grafo no formato de visualizacao.
void gerar_arquivo(string nome_arquivo, vector<Aresta> grafo){

	ofstream escritor;
	escritor.open(nome_arquivo);
	escritor<<"digraph G {\n";
	for(int index=0; index<grafo.size(); index++){
		escritor<<"\t";
		escritor<<to_string(grafo.at(index));
		escritor<<"\n";
	}
	escritor<<"}\n";
	escritor.close();

}

// Programa principal
int main(void){	

	// Captura de um arquivo a Matriz de Ativacao
	int** matrizAtivacao = leMatrizArquivo("MatrizAtivacao.txt", totalAcoes);
	// Exibe Matriz de Ativacao
	cout << "Matriz de Ativacao" << endl;
	exibeMatrizDinamica(matrizAtivacao, totalAcoes);

	// Captura de um arquivo a Matriz de Desativacao
	int** matrizDesativacao = leMatrizArquivo("MatrizDesativacao.txt", totalAcoes);
	// Exibe Matriz de Desativacao
	cout << "Matriz de Desativacao" << endl;
	exibeMatrizDinamica(matrizDesativacao, totalAcoes);

	// Gerando a Matriz de Transicoes
	cs* matrizTransicoes = geraMatrizTransicoes(matrizAtivacao, matrizDesativacao, totalAcoes);
	// Exibe Matriz de Desativacao
	cout << "Matriz de Transicoes" << endl;
	cs_print(matrizTransicoes, 0);

	// Lista de arestas do grafo
	vector<Aresta> grafo;
	// Lista de arestas do grafo
	vector<Aresta> fechoReflexivo;
	// Lista de arestas do grafo
	vector<Aresta> fechoSimetrico;
	// Lista de arestas do grafo
	vector<Aresta> fechoTransitivo;
	// Lista de arestas do grafo
	vector<Aresta> caminho;

	int marcacao;

	// Inicializacao do grafo
	for(int linha = 0; linha< totalAcoes; linha++){
		for(int coluna = 0; coluna< totalAcoes; coluna++){
			marcacao = (int) getEntry(matrizTransicoes, linha, coluna);
			if(marcacao != 0){
				Aresta aresta;
				aresta.origem = linha;
				aresta.destino = coluna;
				grafo.push_back(aresta);
			}
		}
	}

	// Gera o arquivo de visualizacao do grafo
	gerar_arquivo("grafo-completo.dot", grafo);

	// ITENS 1 E 3
	// Selecao do fecho reflexivo
	for(int linha = 0; linha< totalAcoes; linha++){
		marcacao = (int) getEntry(matrizTransicoes, linha, linha);
		if(marcacao != 0){
			Aresta aresta;
			aresta.origem = linha;
			aresta.destino = linha;
			fechoReflexivo.push_back(aresta);
		}
	}
  
	// Verificacao da reflexividade da relacao
	if(!fechoReflexivo.empty()){
		cout << "\n- A relacao eh reflexiva." << endl;
		gerar_arquivo("fecho-reflexivo.dot", fechoReflexivo);
	}

	// Verificacao da irreflexividade da relacao
	for(int linha = 0; linha< totalAcoes; linha++){
		marcacao = (int) getEntry(matrizTransicoes, linha, linha);
		if(marcacao != 0){
			cout << "\n- A relacao nao eh irreflexiva." << endl;
			break;
		}
	}
  
	// Selecao do fecho simetrico
	for(int linha = 0; linha< totalAcoes; linha++){
		for(int coluna = 0; coluna< totalAcoes; coluna++){
			marcacao = (int) getEntry(matrizTransicoes, linha, coluna);
			if(marcacao != 0){
				marcacao = (int) getEntry(matrizTransicoes, coluna, linha);
				if(marcacao != 0){
					Aresta aresta;
					aresta.origem = linha;
					aresta.destino = coluna;
					fechoSimetrico.push_back(aresta);
				}
			}
		}
	}

	// Verificacao da simetria da relacao
	if(!fechoSimetrico.empty()){
		cout << "\n- A relacao eh simetrica." << endl;
		gerar_arquivo("fecho-simetrico.dot", fechoReflexivo);
	}

	// Verificacao da anti-simetria da relacao
	int eh_anti_simetrica = 0;
	for(int linha = 0; linha< totalAcoes; linha++){
		for(int coluna = 0; coluna< totalAcoes; coluna++){
			marcacao = (int) getEntry(matrizTransicoes, linha, coluna);
			if(marcacao != 0){
				marcacao = (int) getEntry(matrizTransicoes, coluna, linha);
				if(marcacao != 0){
					if(linha != coluna){
						cout << "\n- A relacao eh anti-simetrica." << endl;
						eh_anti_simetrica = 1;
						break;
					}
				}
			}
		}
	}

	// Selecao do fecho transitivo
	

	// Verificacao da transitividade da relacao
	if(!fechoTransitivo.empty()){
		cout << "\n- A relacao eh transitiva." << endl;
		gerar_arquivo("fecho-transitivo.dot", fechoReflexivo);
	}

	// ITEM 2
	// Verificacao se a relacao eh equivalente
	if(fechoReflexivo.empty() || fechoSimetrico.empty() || fechoTransitivo.empty()){
		cout << "\n- A relacao nao eh equivalente." << endl;
	}

  
	// Verificacao se a relacao eh de ordem parcial
	if(fechoReflexivo.empty() || (eh_anti_simetrica == 0) || fechoTransitivo.empty()){
		cout << "\n- A relacao nao eh de ordem." << endl;
	}
  
	// ITEM 4
	// Verifica se o sistema eh capaz de retornar ao estado inicial

  
	// ITEM 5
	// Encontra o caminho entre dois nós

	/* Limpando Matrizes */
	free(matrizAtivacao);
	free(matrizDesativacao);
	cs_spfree(matrizTransicoes);

	system("PAUSE > null");
	return 0;
}