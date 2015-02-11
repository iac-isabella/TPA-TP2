# include "matrizEsparsa.h"

/* Função responsável por criar um vetor dinâmicamente dado o tamanho do vetor*/
bool* criaVetorBinario(int tamanhoVetor);

/* Função responsável por criar, dado um número decimal, o vetor binário desse número */
bool* numero2VetorBinario(int numero, int tamanhoVetor, bool* vetor);

/* Função responsável por imprimir um vetor. Como o número é considerado invertido no vetor, essa função auxilia imprimindo o vetor de maneira invertida*/
void imprimeVetorBinario(bool* vetor, int tamanhoVetor);

/* Função responsável por deletar um vetor */
void deletaVetorBinario(bool* vetor);

bool* geraEstadoCandidato(bool* vetorEstadoInicial, bool* vetorTemporario, int tamanhoVetor, bool* vetorEstadoCandidato);
bool* limpaVetorBinario(bool* vetorEstadoCandidato, int tamanhoVetor);
bool verificaVetorVazio(bool* vetorEstadoCandidato, int tamanhoVetor);
bool verificaDependencias(bool* vetorEstadoCandidato, bool* vetorTemporario, matrizEsparsa* matriz, int tamanhoVetor);
void imprimeVetorInteiro(int* vetor, int tamanhoVetor);
