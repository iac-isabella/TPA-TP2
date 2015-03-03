# include "csparse.h"

/* Fun��o respons�vel por criar um vetor din�micamente dado o tamanho do vetor*/
bool* criaVetorBinario(int tamanhoVetor);

/* Fun��o respons�vel por criar, dado um n�mero decimal, o vetor bin�rio desse n�mero */
bool* numero2VetorBinario(int numero, int tamanhoVetor, bool* vetor);

/* Fun��o respons�vel por inserir um valor true em um vetor de falses dado um �ndice */
bool* inserePosVetorBinario(int indice, int tamanhoVetor, bool* vetor);

/* Fun��o respons�vel por imprimir um vetor. Como o n�mero � considerado invertido no vetor, essa fun��o auxilia imprimindo o vetor de maneira invertida*/
void imprimeVetorBinario(bool* vetor, int tamanhoVetor);

/* Fun��o respons�vel por deletar um vetor */
void deletaVetorBinario(bool* vetor);

bool* geraEstadoAtvCandidato(bool* vetorEstadoInicial, bool* vetorTemporario, int tamanhoVetor, bool* vetorEstadoCandidato);
bool* geraEstadoDesCandidato(bool* vetorEstadoInicial, bool* vetorTemporario, int tamanhoVetor, bool* vetorEstadoCandidato);

bool* limpaVetorBinario(bool* vetorEstadoCandidato, int tamanhoVetor);
bool* completaVetorBinario(bool* vetorEstadoCandidato, int tamanhoVetor);

bool verificaVetorVazio(bool* vetorEstadoCandidato, int tamanhoVetor);
bool verificaVetorCheio(bool* vetorEstadoCandidato, int tamanhoVetor);

bool verificaEstadoValido(bool* vetorEstadoCandidato, bool* vetorTemporario, int** matrizRestricao, int tamanhoVetor);

void imprimeVetorInteiro(int* vetor, int tamanhoVetor);
