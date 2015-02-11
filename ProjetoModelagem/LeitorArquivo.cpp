#include <iostream>
#include <fstream>
#include <string>
# include "csparse.h"
using namespace std;
cs* lerMatriz(string nomeArquivo, int numAcoes){
	cs* matriz = cs_spalloc(numAcoes, numAcoes, numAcoes, 1, 1);
	ifstream inFile (nomeArquivo.c_str( ) );
	if(!inFile ) {
		cerr << "Não foi possivel abrir o arquivo de entrada : "
			<< nomeArquivo << " Saindo do programa!\n";
		return nullptr;	}
	string linha;
	int i, j = 0;
	while (inFile.getline(linha)) {

	}
}