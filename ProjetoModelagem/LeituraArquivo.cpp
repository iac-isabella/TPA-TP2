#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

queue<string> leLog(){
	char depot[300];
	ifstream leArquivo;
	leArquivo.open("C:\\Users\\T\\Google Drive\\Inicia��o Cient�fica\\Programas\\LogEventos.txt");
	if (!leArquivo.is_open()) {
		cout << "N�o foi poss�vel abrir arquivo!\n";
		leArquivo.clear();
	}
	queue<string> linhasArquivo;
	while (leArquivo.getline(depot, 300))
		linhasArquivo.push(depot);
	leArquivo.close();
	return linhasArquivo;
}