#include <iostream>
using namespace std;

void exibeMatrizDinamica(int** matriz, int tam){
	for (int i = 0; i < tam; i++){
		for (int j = 0; j < tam; j++){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}