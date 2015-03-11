# include <iostream>
# include <queue>
#include <vector>
# include <string>
#include <fstream>
#include<math.h>
# include "ManipulaArquivo.h"
# include "ImprimeMatriz.h"
# include "MatrizTransicoes.h"
# include "csparse.h"
using namespace std;

// Definindo o total de acoes do modelo
# define totalAcoes 3

# define branco 0
# define cinza 1

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
	for(int index=0; index < grafo.size(); index++){
		escritor<<"\t";
		escritor<<to_string(grafo.at(index));
		escritor<<"\n";
	}
	escritor<<"}\n";
	escritor.close();

}

void visitar(int u, cs* matriz, int n, int* cor, int* pred){
	int v;
	cor[u] = cinza;
    for(v =0; v<n; v++){
   		if((int) getEntry(matriz, u, v) != 0) {
			if (cor[v] == branco){
		        pred[v] = u;
		        visitar(v,matriz,n, cor, pred);
			}
		}
	}
}

void busca_em_profundidade(cs* matriz, int n, int estadoInicial, int* cor, int* pred){
  for (int i =0;i<n;i++){
	cor[i]= branco;
	pred[i]=0;
  }
  visitar(estadoInicial,matriz,n, cor, pred);
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
	int totalEstados = (int) pow(2, totalAcoes);

	// Inicializacao do grafo
	for(int linha = 1; linha<= totalEstados; linha++){
		for(int coluna = 1; coluna<= totalEstados; coluna++){
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
	int reflexivo = 1;
	for(int linha = 1; linha<= totalEstados; linha++){
		marcacao = (int) getEntry(matrizTransicoes, linha, linha);
		if(marcacao != 0){
			Aresta aresta;
			aresta.origem = linha;
			aresta.destino = linha;
			fechoReflexivo.push_back(aresta);
		} else{
			reflexivo = 0;
		}
	}
  
	// Verificacao da reflexividade da relacao
	if(!fechoReflexivo.empty()){
		if(reflexivo != 0){
			cout << "\n- A relacao eh reflexiva." << endl;
		}
		gerar_arquivo("fecho-reflexivo.dot", fechoReflexivo);
	} else{
		// Verificacao da irreflexividade da relacao
		cout << "\n- A relacao eh irreflexiva." << endl;
	}

	// Selecao do fecho simetrico
	int simetrico = 1;
	for(int linha = 1; linha<= totalEstados; linha++){
		for(int coluna = 1; coluna<= totalEstados; coluna++){
			marcacao = (int) getEntry(matrizTransicoes, linha, coluna);
			if(marcacao != 0){
				marcacao = (int) getEntry(matrizTransicoes, coluna, linha);
				if(marcacao != 0){
					Aresta aresta;
					aresta.origem = linha;
					aresta.destino = coluna;
					fechoSimetrico.push_back(aresta);
				} else{
					simetrico = 0;
				}
			}
		}
	}

	// Verificacao da simetria da relacao
	if(!fechoSimetrico.empty()){
		if(simetrico != 0){
			cout << "\n- A relacao eh simetrica." << endl;
		}
		gerar_arquivo("fecho-simetrico.dot", fechoSimetrico);
	} else{
		// Verificacao da assimetria da relacao
		cout << "\n- A relacao eh assimetrica." << endl;
	}

	// Verificacao da anti-simetria da relacao
	int antiSimetrico = 0;
	for(int linha = 1; linha<= totalEstados && antiSimetrico == 0; linha++){
		for(int coluna = 1; coluna<= totalEstados && antiSimetrico == 0; coluna++){
			marcacao = (int) getEntry(matrizTransicoes, linha, coluna);
			if(marcacao != 0){
				marcacao = (int) getEntry(matrizTransicoes, coluna, linha);
				if(marcacao != 0){
					if(linha != coluna){
						cout << "\n- A relacao eh anti-simetrica." << endl;
						antiSimetrico = 1;
					}
				}
			}
		}
	}

	// Selecao do fecho transitivo
	int transitivo = 1;
	Aresta a;
	Aresta b;
	Aresta c;
	// Para cada aresta do grafo
	for (int i = 0; i<grafo.size(); i++){
		vector<Aresta> adjOrigem;
		vector<Aresta> adjDestino;
		int cont = 0;
		a = grafo.at(i);

		// Para cada aresta do grafo
		for (int j = 0; j<grafo.size(); j++){
			b = grafo.at(j);
			// Verifica se a aresta b tem a mesma origem da aresta a e inclui na lista de adjacentes a origem
			if (b.origem == a.origem && j!=i && b.origem != b.destino){
				Aresta aresta;
				aresta.origem = b.origem;
				aresta.destino = b.destino;
				adjOrigem.push_back(aresta);
			} else{
				// Verifica se a aresta b tem o mesmo destino da aresta a e inclui na lista de adjacentes ao destino
				if (b.destino == a.destino && j!=i  && b.origem != b.destino){
					Aresta aresta;
					aresta.origem = b.origem;
					aresta.destino = b.destino;
					adjDestino.push_back(aresta);
				}
			}
		}
		// Procura nas listas de adjacentes a origem e destino, quais arestas tem em comum o destino e a origem e inclui no fecho
		for (int j = 0; j<adjOrigem.size(); j++){
			b = adjOrigem.at(j);
			for (int k = 0; k<adjDestino.size(); k++){
				c = adjDestino.at(k);
				if (b.destino == c.origem){
					fechoTransitivo.push_back(b);
					fechoTransitivo.push_back(c);
					cont++;
				}
			}
		}
		// Inclui a aresta a no fecho se a relação eh valida
		if (cont>0){
			fechoTransitivo.push_back(a);
		}
		else{
			transitivo = 0;
		}
	}

	// Verificacao da transitividade da relacao
	if(!fechoTransitivo.empty()){
		if(transitivo != 0){
			cout << "\n- A relacao eh transitiva." << endl;
		}
		gerar_arquivo("fecho-transitivo.dot", fechoTransitivo);
	}

	// ITEM 2
	// Verificacao se a relacao eh equivalente
	if((reflexivo == 0) || (simetrico == 0) || (transitivo == 0)){
		cout << "\n- A relacao nao eh equivalente." << endl;
	} else{
		cout << "\n- A relacao eh equivalente." << endl;
	}

  
	// Verificacao se a relacao eh de ordem parcial
	if((reflexivo == 0) || (antiSimetrico == 0) || (transitivo == 0)){
		cout << "\n- A relacao nao eh de ordem." << endl;
	} else{
		cout << "\n- A relacao nao eh de ordem." << endl;
	}
  
	// ITEM 4
	// Verifica se o sistema eh capaz de retornar ao estado inicial
	int* cor = (int*) malloc(totalEstados*sizeof(int));
	int* pred = (int*) malloc(totalEstados*sizeof(int));
	if(cor != NULL && pred != NULL){
		busca_em_profundidade(matrizTransicoes, totalEstados, 1, cor, pred);
		int reset = 0;
		for(int i = 0; i<totalEstados; i++){
			if(pred[i] == 1){
				reset = 1;
				break;
			}
		}
		if(reset == 1){
			cout << "\n- o sistema eh reiniciavel." << endl;
			cout << "A partir dos estados:" << endl;
			for(int i = 0; i<totalEstados; i++){
				if(pred[i] != 1){
					cout << i+1 << endl;
				}
			}
		}
		
	}
	// ITEM 5
	// Encontra o caminho entre dois nós
	cout << "\n- Mostrando estados alcancaveis a partir da origem:" << endl;
	for(int i = 0; i<totalEstados; i++){
		cout << pred[i] << endl;
	}

	/* Limpando Matrizes */
	free(matrizAtivacao);
	free(matrizDesativacao);
	cs_spfree(matrizTransicoes);

	cout << "\nProcessamento concluido." << endl;

	system("PAUSE > null");
	return 0;
}