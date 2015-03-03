# include "csparse.h"

/* Função responsável por criar um vetor dinâmicamente dado o tamanho do vetor*/
bool* criaVetorBinario(int tamanhoVetor);

/* Função responsável por criar, dado um número decimal, o vetor binário desse número */
bool* numero2VetorBinario(int numero, int tamanhoVetor, bool* vetor);

/* Função responsável por inserir um valor true em um vetor de falses dado um índice */
bool* inserePosVetorBinario(int indice, int tamanhoVetor, bool* vetor);

/* Função responsável por imprimir um vetor. Como o número é considerado invertido no vetor, essa função auxilia imprimindo o vetor de maneira invertida*/
void imprimeVetorBinario(bool* vetor, int tamanhoVetor);

/* Função responsável por deletar um vetor */
void deletaVetorBinario(bool* vetor);

bool* geraEstadoAtvCandidato(bool* vetorEstadoInicial, bool* vetorTemporario, int tamanhoVetor, bool* vetorEstadoCandidato);
bool* geraEstadoDesCandidato(bool* vetorEstadoInicial, bool* vetorTemporario, int tamanhoVetor, bool* vetorEstadoCandidato);

bool* limpaVetorBinario(bool* vetorEstadoCandidato, int tamanhoVetor);
bool* completaVetorBinario(bool* vetorEstadoCandidato, int tamanhoVetor);

bool verificaVetorVazio(bool* vetorEstadoCandidato, int tamanhoVetor);
bool verificaVetorCheio(bool* vetorEstadoCandidato, int tamanhoVetor);

bool verificaEstadoValido(bool* vetorEstadoCandidato, bool* vetorTemporario, int** matrizRestricao, int tamanhoVetor);

void imprimeVetorInteiro(int* vetor, int tamanhoVetor);
