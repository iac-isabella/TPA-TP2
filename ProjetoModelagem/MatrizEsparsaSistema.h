struct matrizEsparsa;
struct noListaPrimariaS;
struct noListaSecundariaS;
struct noListaElemento;

// Função necessária pra criar uma matriz do sistema
matrizEsparsa* geraMatrizEsparsa();

// Função responsável para criar um nó
noListaElemento* criaNo(bool ehObrigatorio, bool ehFinal);

// Função responsável para adicionar o nó
void adicionaNo(matrizEsparsa* matrizEsparsa, noListaElemento* elemento, int linha, int coluna);
// Funções necessárias para inserir um elemento
noListaPrimariaS* encontraNoListaPrimaria(matrizEsparsa* matrizEsparsa, int linha);
noListaSecundariaS* encontraNoListaSecundaria(noListaPrimariaS* noP, int coluna);
void insereElemento(noListaSecundariaS* noS, noListaElemento* elemento);

// Verifica se elemento existe
bool existe(matrizEsparsa* matrizEsparsa, int linha, int coluna);
// Função necessária para verificar se elemento existe
bool procuraColuna(noListaPrimariaS* noP, int coluna);

// Função que imprime uma matriz do sistema
void imprimeMatrizEsparsa(matrizEsparsa* matrizEsparsa, int tamanhoMatriz);