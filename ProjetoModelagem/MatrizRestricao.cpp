# include <queue>
# include "ManipulaArquivo.h"
# include "MatrizEsparsaRestricao.h"
using namespace std;

queue<matrizEsparsaR*> geraMatrizesRestricao(int numeroTarefas, regras* regras){
	
	// Cria a primeira matriz de restri��o nula e a insere na fila
	matrizEsparsaR* matrizPai = geraMatrizEsparsaR(numeroTarefas);

	// Cria a matriz conforme as depend�ncias
    // matrizPai = regraDependencia(matrizPai);

	// Cria uma fila vazia para armazenar as matrizes de restri��o
	queue<matrizEsparsaR*> filaMatrizesRestricao;


	return filaMatrizesRestricao;
}