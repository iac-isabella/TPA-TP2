# include <queue>
# include "ManipulaArquivo.h"
# include "MatrizEsparsaRestricao.h"
using namespace std;

queue<matrizEsparsaR*> geraMatrizesRestricao(int numeroTarefas, regras* regras){
	
	// Cria a primeira matriz de restrição nula e a insere na fila
	matrizEsparsaR* matrizPai = geraMatrizEsparsaR(numeroTarefas);

	// Cria a matriz conforme as dependências
    // matrizPai = regraDependencia(matrizPai);

	// Cria uma fila vazia para armazenar as matrizes de restrição
	queue<matrizEsparsaR*> filaMatrizesRestricao;


	return filaMatrizesRestricao;
}