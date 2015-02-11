#include <iostream>
# include "matrizEsparsaSistema.h"
using namespace std;

struct matrizEsparsa{
	noListaPrimariaS* primeiroNoListaPrimaria = nullptr;
};

struct noListaPrimariaS{
	int indiceY;
	noListaSecundariaS* primeiroNoListaSecundaria = nullptr;
	noListaPrimariaS* proximoNoListaPrimaria = nullptr;
};

struct noListaSecundariaS{
	int indiceX;
	noListaElemento* primeiroNoListaElementos = nullptr;
	noListaSecundariaS* proximoNoListaSecundaria = nullptr;
};

struct noListaElemento{
	bool ehObrigatorio;
	bool ehFinal;
	// Dado dois elementos que se encontram na mesma posição, podemos visitar o próximo através do nó "próximo"
	noListaElemento* proximo = nullptr;
};

noListaElemento* criaNo(bool ehObrigatorio, bool ehFinal){
	noListaElemento* no = new noListaElemento();
	no->ehObrigatorio = ehObrigatorio;
	no->ehFinal = ehFinal;
	return no;
}

matrizEsparsa* geraMatrizEsparsa(){
	matrizEsparsa* matrizEsparsa = new matrizEsparsa();
	return matrizEsparsa;
}

void adicionaNo(matrizEsparsa* matrizEsparsa, noListaElemento* elemento, int linha, int coluna){
	// Localiza a posição para a inserção na lista primaria
	noListaPrimariaS* noP = encontraNoListaPrimaria(matrizEsparsa, linha);
	// Localiza a posição para a inserção na lista primaria
	noListaSecundariaS* noS = encontraNoListaSecundaria(noP, coluna);
	// Insere elemento
	insereElemento(noS, elemento);
}


noListaPrimariaS* encontraNoListaPrimaria(matrizEsparsa* matrizEsparsa, int linha){

	// Cria-se um nó da lista primária
	noListaPrimariaS* noP = new noListaPrimariaS;
	noP->indiceY = linha;

	// Se a matriz esparsa não possui nenhum elemento ainda
	if (matrizEsparsa->primeiroNoListaPrimaria == nullptr)
		matrizEsparsa->primeiroNoListaPrimaria = noP;
	// Se matriz esparsa possui elementos
	else{
		// Se for igual
		if (matrizEsparsa->primeiroNoListaPrimaria->indiceY == linha){
			noP = matrizEsparsa->primeiroNoListaPrimaria;
		}
		// Se for maior (Se o noEixoX ainda não existe e se encontra antes do primeiro noEixoX)
		else if (matrizEsparsa->primeiroNoListaPrimaria->indiceY > linha){
			noP->proximoNoListaPrimaria = matrizEsparsa->primeiroNoListaPrimaria;
			matrizEsparsa->primeiroNoListaPrimaria = noP;
		}
		// Se o noEixoX não deve ser inserido logo na primeira posição
		else {
			// Cria um nó do eixo X para percorrer os elementos do eixo X
			noListaPrimariaS* caminhaListaPrimaria = matrizEsparsa->primeiroNoListaPrimaria;
			bool encontrouPosicao = false;
			while (caminhaListaPrimaria->proximoNoListaPrimaria != nullptr && !encontrouPosicao){
				// Se o próximo elemento possui um índice maior ou igual a coluna
				// Se for igual
				if (caminhaListaPrimaria->proximoNoListaPrimaria->indiceY == linha){
					encontrouPosicao = true;
					noP = caminhaListaPrimaria->proximoNoListaPrimaria;
				}
				// Se for maior (Se o noEixoX ainda não existe e se encontra antes do noEixoX apontado por caminhaEixoX->proximoNoEixoX)
				else if (caminhaListaPrimaria->proximoNoListaPrimaria->indiceY > linha){
						encontrouPosicao = true;
						noP->proximoNoListaPrimaria = caminhaListaPrimaria->proximoNoListaPrimaria;
						caminhaListaPrimaria->proximoNoListaPrimaria = noP;
				}
				// Se o próximo elemento possui um índice menor que a coluna
				else
					caminhaListaPrimaria = caminhaListaPrimaria->proximoNoListaPrimaria;
			}
			// Se percorreu todo o eixo X e não encontrou posição, significa que a coluna é maior que a atual matriz
			if (!encontrouPosicao){
				caminhaListaPrimaria->proximoNoListaPrimaria = noP;
				noP->proximoNoListaPrimaria = nullptr;
			}
		}
	}
	return noP;
}

noListaSecundariaS* encontraNoListaSecundaria(noListaPrimariaS* noP, int coluna){
	
	// Cria-se o nó da lista secundária
	noListaSecundariaS* noS = new noListaSecundariaS();
	noS->indiceX = coluna;

	// Se o noP não possuir nenhum elemento
	if (noP->primeiroNoListaSecundaria == nullptr){
		noP->primeiroNoListaSecundaria = noS;
	}
	// Se matriz esparsa possui elementos
	else{
		// Se o primeiro elemento já for igual a coluna
		if (noP->primeiroNoListaSecundaria->indiceX == coluna){
			noS = noP->primeiroNoListaSecundaria;
		}
		// Se for maior
		else if (noP->primeiroNoListaSecundaria->indiceX > coluna){
			noS->proximoNoListaSecundaria = noP->primeiroNoListaSecundaria;
			noP->primeiroNoListaSecundaria = noS;
		}
		// Se for menor (não será inserido na primeira posição)
		else {
			// Cria um nó do eixo X para percorrer os elementos do eixo X
			noListaSecundariaS* caminhaListaSecundaria = noP->primeiroNoListaSecundaria;
			bool encontrouPosicao = false;
			while (caminhaListaSecundaria->proximoNoListaSecundaria != nullptr && !encontrouPosicao){
				// Se for igual
				if (caminhaListaSecundaria->proximoNoListaSecundaria->indiceX == coluna){
					encontrouPosicao = true;
					noS = caminhaListaSecundaria->proximoNoListaSecundaria;
				}
				// Se for maior
				else if (caminhaListaSecundaria->proximoNoListaSecundaria->indiceX > coluna){
					encontrouPosicao = true;
					noS->proximoNoListaSecundaria = caminhaListaSecundaria->proximoNoListaSecundaria;
					caminhaListaSecundaria->proximoNoListaSecundaria = noS;
				}
				// Se o próximo elemento possui um índice menor que a coluna
				else
					caminhaListaSecundaria = caminhaListaSecundaria->proximoNoListaSecundaria;
			}
			// Se percorreu todo o eixo X e não encontrou posição, significa que a coluna é maior que a atual matriz
			if (!encontrouPosicao){
				caminhaListaSecundaria->proximoNoListaSecundaria = noS;
				noS->proximoNoListaSecundaria = nullptr;
			}
		}
	}
	return noS;
}

void insereElemento(noListaSecundariaS* noS,noListaElemento* elemento){
	if (noS->primeiroNoListaElementos == nullptr)
		noS->primeiroNoListaElementos = elemento;
	else{
		noListaElemento* caminhaElementos = new noListaElemento();
		caminhaElementos = noS->primeiroNoListaElementos;
		while (caminhaElementos->proximo != nullptr)
			caminhaElementos = caminhaElementos->proximo;
		caminhaElementos->proximo = elemento;
	}
}

bool existe(matrizEsparsa* matrizEsparsa, int linha, int coluna){
	if (matrizEsparsa->primeiroNoListaPrimaria->indiceY == linha)
		return procuraColuna(matrizEsparsa->primeiroNoListaPrimaria, coluna);
	else{
		noListaPrimariaS* caminhaLinha = new noListaPrimariaS();
		caminhaLinha = matrizEsparsa->primeiroNoListaPrimaria;
		while (caminhaLinha != nullptr){
			if (caminhaLinha->indiceY == linha)
				return procuraColuna(caminhaLinha, coluna);
			caminhaLinha = caminhaLinha->proximoNoListaPrimaria;
		}
	}
	return false;
}

bool procuraColuna(noListaPrimariaS* noP, int coluna){
	noListaSecundariaS* caminhaColuna = new noListaSecundariaS();
	caminhaColuna = noP->primeiroNoListaSecundaria;
	if (caminhaColuna->indiceX == coluna)
		return true;
	while (caminhaColuna != nullptr){
		if (caminhaColuna->indiceX == coluna)
			return true;
		else if (caminhaColuna->indiceX > coluna)
			return false;
		caminhaColuna = caminhaColuna->proximoNoListaSecundaria;
	}
	return false;
}

void imprimeMatrizEsparsa(matrizEsparsa* matrizEsparsa, int tamanhoMatriz){
	int linha = 1;
	noListaPrimariaS* caminhaLinha = matrizEsparsa->primeiroNoListaPrimaria;
	while (caminhaLinha != nullptr){
		// Caso uma linha não exista no fluxo, imprima uma linha de 2's
		while (linha < caminhaLinha->indiceY){
			for (int escreveLinha = 1; escreveLinha <= tamanhoMatriz; escreveLinha++)
				cout << "2" << " ";
			cout << endl;
			linha++;
		}
		noListaSecundariaS* caminhaColuna = caminhaLinha->primeiroNoListaSecundaria;
		for (int coluna = 1; coluna <= tamanhoMatriz; coluna++){
			cout << caminhaColuna->valor << " ";
			caminhaColuna = caminhaColuna->proximoNoListaSecundaria;
		}
		linha++;
		caminhaLinha = caminhaLinha->proximoNoListaPrimaria;
		cout << endl;
	}
	// Linhas finais que foram excluídas
	while (linha <= tamanhoMatriz){
		for (int escreveLinha = 1; escreveLinha <= tamanhoMatriz; escreveLinha++)
			cout << "2" << " ";
		cout << endl;
		linha++;
	}
	cout << endl;
}