#include <fstream>
using namespace std;

int** leMatrizArquivo(char* endereco, int tam){
	int **matriz;
	ifstream arquivo;

	// Abre arquivo
	arquivo.open(endereco);

	// Aloca memória para a matriz
	matriz = (int **) malloc(tam * sizeof(int *));

	// Aloca a memória
	for (int linha = 0; linha < tam; linha++){
		matriz[linha] = (int *) malloc(tam * sizeof(int));
	}

	// Preenche a matriz
	for (int i = 0; i < tam; i++){
		for (int j = 0; j < tam; j++){
			arquivo >> matriz[i][j];
		}
	}

	return matriz;
}
