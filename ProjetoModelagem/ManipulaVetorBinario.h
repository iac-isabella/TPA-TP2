# include "matrizEsparsa.h"

/* Fun��o respons�vel por criar um vetor din�micamente dado o tamanho do vetor*/
bool* criaVetorBinario(int tamanhoVetor);

/* Fun��o respons�vel por criar, dado um n�mero decimal, o vetor bin�rio desse n�mero */
bool* numero2VetorBinario(int numero, int tamanhoVetor, bool* vetor);

/* Fun��o respons�vel por imprimir um vetor. Como o n�mero � considerado invertido no vetor, essa fun��o auxilia imprimindo o vetor de maneira invertida*/
void imprimeVetorBinario(bool* vetor, int tamanhoVetor);

/* Fun��o respons�vel por deletar um vetor */
void deletaVetorBinario(bool* vetor);

bool* geraEstadoCandidato(bool* vetorEstadoInicial, bool* vetorTemporario, int tamanhoVetor, bool* vetorEstadoCandidato);
bool* limpaVetorBinario(bool* vetorEstadoCandidato, int tamanhoVetor);
bool verificaVetorVazio(bool* vetorEstadoCandidato, int tamanhoVetor);
bool verificaDependencias(bool* vetorEstadoCandidato, bool* vetorTemporario, matrizEsparsa* matriz, int tamanhoVetor);
void imprimeVetorInteiro(int* vetor, int tamanhoVetor);
