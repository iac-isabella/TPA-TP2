#include <iostream>
# include "matrizEsparsa.h"
using namespace std;

struct matrizEsparsa{
	noListaPrimariaR* primeiroNoListaPrimaria = nullptr;
};

struct noListaPrimariaR{
	int indiceY;
	noListaSecundariaR* primeiroNoListaSecundaria = nullptr;
	noListaPrimariaR* proximoNoListaPrimaria = nullptr;
};

struct noListaSecundariaR{
	int indiceX;
	bool valor;
	noListaSecundariaR* proximoNoListaSecundaria = nullptr;
};

matrizEsparsa* geraMatrizEsparsa(int tamanhoMatriz){
	matrizEsparsa* matriz = new matrizEsparsa();
	for (int coluna = 1; coluna <= tamanhoMatriz; coluna++)
		for (int linha = 1; linha <= tamanhoMatriz; linha++)
			insereDependencia(matriz, false, linha, coluna);
	return matriz;
}

void insereDependencia(matrizEsparsa* matrizEsparsa, bool valor, int linha, int coluna){
	// Localiza a posição para a inserção na lista primaria
	noListaPrimariaR* noP = encontraNoListaPrimaria(matrizEsparsa, linha);
	// Localiza a posição para a inserção na lista primaria
	noListaSecundariaR* noS = encontraNoListaSecundaria(noP, coluna);
	// Insere elemento
	noS->valor = valor;
}

noListaPrimariaR* encontraNoListaPrimaria(matrizEsparsa* matrizEsparsa, int linha){

	// Cria-se um nó da lista primária
	noListaPrimariaR* noP = new noListaPrimariaR;
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
			noListaPrimariaR* caminhaListaPrimaria = matrizEsparsa->primeiroNoListaPrimaria;
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

noListaSecundariaR* encontraNoListaSecundaria(noListaPrimariaR* noP, int coluna){

	// Cria-se o nó da lista secundária
	noListaSecundariaR* noS = new noListaSecundariaR();
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
			noListaSecundariaR* caminhaListaSecundaria = noP->primeiroNoListaSecundaria;
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

void excluiTarefa(matrizEsparsa* matrizEsparsa, int linha){
	// Se a matriz não se encontrar vazia (sem tarefas possíveis por fluxo)
	if (matrizEsparsa->primeiroNoListaPrimaria != nullptr){
		// Se a linha a ser eliminada se encontra na primeira posição
		if (matrizEsparsa->primeiroNoListaPrimaria->indiceY == linha)
			matrizEsparsa->primeiroNoListaPrimaria = matrizEsparsa->primeiroNoListaPrimaria->proximoNoListaPrimaria;
		// Senão
		else{
			noListaPrimariaR* caminhaLinha = matrizEsparsa->primeiroNoListaPrimaria;
			bool encontrouTarefa = false;
			// Se for algum elemento no meio ou no final da lista
			while (caminhaLinha->proximoNoListaPrimaria != nullptr && !encontrouTarefa){
				if (caminhaLinha->proximoNoListaPrimaria->indiceY == linha){
					caminhaLinha->proximoNoListaPrimaria = caminhaLinha->proximoNoListaPrimaria->proximoNoListaPrimaria;
					encontrouTarefa = true;
				}
				else
					caminhaLinha = caminhaLinha->proximoNoListaPrimaria;
			}
		}
	}
}

bool tarefaExisteFluxo(matrizEsparsa* matrizEsparsa, int linha){
	if (matrizEsparsa->primeiroNoListaPrimaria != nullptr){
		if (matrizEsparsa->primeiroNoListaPrimaria->indiceY == linha)
			return true;
		else{
			noListaPrimariaR* caminhaLinha = matrizEsparsa->primeiroNoListaPrimaria;
			while (caminhaLinha != nullptr){
				if (caminhaLinha->indiceY == linha)
					return true;
				caminhaLinha = caminhaLinha->proximoNoListaPrimaria;
			}
		}
	}
	return false;
}

bool valorPosicao(matrizEsparsa* matrizEsparsa, int linha, int coluna){
	noListaPrimariaR* noP = matrizEsparsa->primeiroNoListaPrimaria;
	while (noP != nullptr){
		if (noP->indiceY == linha){
			noListaSecundariaR* noS = noP->primeiroNoListaSecundaria;
			while (noS != nullptr){
				if (noS->indiceX == coluna)
					return noS->valor;
				// Precaução
				if (noS->indiceX > coluna)
					return 0;
				noS = noS->proximoNoListaSecundaria;
			}
		}
		// Precaução
		if (noP->indiceY > linha)
			return 0;
		noP = noP->proximoNoListaPrimaria;
	}
	return 0;
}

void imprimeMatrizEsparsa(matrizEsparsa* matrizEsparsa, int tamanhoMatriz){
	int linha = 1;
	noListaPrimariaR* caminhaLinha = matrizEsparsa->primeiroNoListaPrimaria;
	while(caminhaLinha != nullptr){
		// Caso uma linha não exista no fluxo, imprima uma linha de 2's
		while (linha < caminhaLinha->indiceY){
			for (int escreveLinha = 1; escreveLinha <= tamanhoMatriz;escreveLinha++)
				cout << "2" << " ";
			cout << endl;
			linha++;
		}
		noListaSecundariaR* caminhaColuna = caminhaLinha->primeiroNoListaSecundaria;
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

////////////////////////////////////////////////////////////////////////////////

void adicionaValor(matrizEsparsa* matrizEsparsa, int valor, int linha, int coluna){
	// Localiza a posição para a inserção na lista primaria
	noListaPrimariaR* noP = encontraNoListaPrimaria(matrizEsparsa, linha);
	// Localiza a posição para a inserção na lista primaria
	noListaSecundariaR* noS = encontraNoListaSecundaria(noP, coluna);
	// Insere elemento-
	insereElemento(noS, valor);
}

noListaPrimariaR* encontraNoListaPrimariaS(matrizEsparsa* matrizEsparsa, int linha){
	// Cria-se um nó da lista primária
	noListaPrimariaR* noP = new noListaPrimariaR;
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
			noListaPrimariaR* caminhaListaPrimaria = matrizEsparsa->primeiroNoListaPrimaria;
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

noListaSecundariaR* encontraNoListaSecundariaS(noListaPrimariaR* noP, int coluna){
	// Cria-se o nó da lista secundária
	noListaSecundariaR* noS = new noListaSecundariaR();
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
			noListaSecundariaR* caminhaListaSecundaria = noP->primeiroNoListaSecundaria;
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

void insereElemento(noListaSecundariaR* noS, int valor){
	/*
	if (noS->primeiroNoListaElementos == nullptr)
		noS->primeiroNoListaElementos = elemento;
	else{
		noListaElemento* caminhaElementos = new noListaElemento();
		caminhaElementos = noS->primeiroNoListaElementos;
		while (caminhaElementos->proximo != nullptr)
			caminhaElementos = caminhaElementos->proximo;
		caminhaElementos->proximo = elemento;
	}
	*/
}

bool existe(matrizEsparsa* matrizEsparsa, int linha, int coluna){
	if (matrizEsparsa->primeiroNoListaPrimaria->indiceY == linha)
		return procuraColuna(matrizEsparsa->primeiroNoListaPrimaria, coluna);
	else{
		noListaPrimariaR* caminhaLinha = new noListaPrimariaR();
		caminhaLinha = matrizEsparsa->primeiroNoListaPrimaria;
		while (caminhaLinha != nullptr){
			if (caminhaLinha->indiceY == linha)
				return procuraColuna(caminhaLinha, coluna);
			caminhaLinha = caminhaLinha->proximoNoListaPrimaria;
		}
	}
	return false;
}

bool procuraColuna(noListaPrimariaR* noP, int coluna){
	noListaSecundariaR* caminhaColuna = new noListaSecundariaR();
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