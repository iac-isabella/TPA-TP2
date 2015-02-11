# include <iostream>
# include <queue>
# include <string>
# include "MatrizSistema.h"
# include "MatrizEsparsa.h"
# include <dsparse.h>
using namespace std;

int main(void)
{
	/*
	manipulaArquivo();
	queue<matrizEsparsa*> listaMatrizesRestricao;
	matrizEsparsa* matriz1 = geramatrizEsparsa(3);
	matrizEsparsa* matriz2 = geramatrizEsparsa(3);

	listaMatrizesRestricao.push(matriz1);
	listaMatrizesRestricao.push(matriz2);
	*/
	
	//int matrizRestricao[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
	int numeroTarefas = 3;
	matrizEsparsa* matrizRestricao = geraMatrizEsparsa(numeroTarefas);
	matrizEsparsa* matrizSistema = geraMatrizSistema(matrizRestricao);
	imprimeMatrizEsparsa(matrizSistema, 8);
	system("PAUSE > null");
	return 0;
}