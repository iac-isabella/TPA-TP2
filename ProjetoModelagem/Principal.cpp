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

// Estrutura de dados que representa uma Aresta.
typedef struct {

	int origem;
	int destino;

} Aresta;

// Estrutura de dados que representa um Vertice.
typedef struct {

	int estado;
	int predecessor;
	int visitado;

} Vertice;

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

vector<Vertice> montar_lista_adjacencias(int estado, vector<Aresta> grafo){
	vector<Vertice> adjacencias;
	Aresta a;
	for(int index=0; index<grafo.size(); index++){
		a = grafo.at(index);
		if(a.origem == estado){
			Vertice v;
			v.estado = a.destino;
			v.predecessor = a.origem;
			v.visitado = 0;
			adjacencias.push_back(v);
		}
	}
	return adjacencias;
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
	for(int linha = 0; linha< totalEstados; linha++){
		for(int coluna = 0; coluna< totalEstados; coluna++){
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
	for(int linha = 0; linha< totalEstados; linha++){
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
	for(int linha = 0; linha< totalEstados; linha++){
		for(int coluna = 0; coluna< totalEstados; coluna++){
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
		gerar_arquivo("fecho-simetrico.dot", fechoReflexivo);
	} else{
		// Verificacao da assimetria da relacao
		cout << "\n- A relacao eh assimetrica." << endl;
	}

	// Verificacao da anti-simetria da relacao
	int antiSimetrico = 0;
	for(int linha = 0; linha< totalEstados && antiSimetrico == 0; linha++){
		for(int coluna = 0; coluna< totalEstados && antiSimetrico == 0; coluna++){
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
	if(grafo.size()>0){
		vector<Vertice> vertices;
		queue<int> fila;
		int u;
		for(int index = 0; index<totalEstados; index++){
			Vertice v;
			v.estado = index;
			v.predecessor = -1;
			v.visitado = 0;
			vertices.push_back(v);
		}
		fila.push(0);
		while (!fila.empty()){
			u = fila.front();
			vector<Vertice> adj = montar_lista_adjacencias(u, grafo);
			for(int i = 0; i<adj.size(); i++){

			}
			fila.pop();
		}
  enquanto Q não está vazia faça
      u := PRIMEIRO-DA-FILA(Q)
      para cada v em Adj[u] faça
          se dist[u] + len(u,v) < dist[v] então
            estado[v] := ROTULADO
            dist[v] := dist[u]+len(u,v)
            pred[v] := u
            se v não está em Q então 
              INSIRA-NA-FILA(Q,v)
      REMOVA-DA-FILA(Q)
      estado[u] := EXAMINADO
  devolva dist e pred
	} else{
		transitivo = 0;
	}


	// Verificacao da transitividade da relacao
	if(!fechoTransitivo.empty()){
		if(transitivo != 0){
			cout << "\n- A relacao eh transitiva." << endl;
		}
		gerar_arquivo("fecho-transitivo.dot", fechoReflexivo);
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
	
  
	// ITEM 5
	// Encontra o caminho entre dois nós

	/* Limpando Matrizes */
	free(matrizAtivacao);
	free(matrizDesativacao);
	cs_spfree(matrizTransicoes);

	cout << "\nProcessamento concluido." << endl;

	system("PAUSE > null");
	return 0;
}