struct matrizEsparsa;
struct noListaPrimariaS;
struct noListaSecundariaS;
struct noListaElemento;

// Fun��o necess�ria pra criar uma matriz do sistema
matrizEsparsa* geraMatrizEsparsa();

// Fun��o respons�vel para criar um n�
noListaElemento* criaNo(bool ehObrigatorio, bool ehFinal);

// Fun��o respons�vel para adicionar o n�
void adicionaNo(matrizEsparsa* matrizEsparsa, noListaElemento* elemento, int linha, int coluna);
// Fun��es necess�rias para inserir um elemento
noListaPrimariaS* encontraNoListaPrimaria(matrizEsparsa* matrizEsparsa, int linha);
noListaSecundariaS* encontraNoListaSecundaria(noListaPrimariaS* noP, int coluna);
void insereElemento(noListaSecundariaS* noS, noListaElemento* elemento);

// Verifica se elemento existe
bool existe(matrizEsparsa* matrizEsparsa, int linha, int coluna);
// Fun��o necess�ria para verificar se elemento existe
bool procuraColuna(noListaPrimariaS* noP, int coluna);

// Fun��o que imprime uma matriz do sistema
void imprimeMatrizEsparsa(matrizEsparsa* matrizEsparsa, int tamanhoMatriz);