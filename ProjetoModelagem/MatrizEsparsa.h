struct matrizEsparsa;
struct noListaPrimariaR;
struct noListaSecundariaR;

// Função que cria uma matriz de restrição
matrizEsparsa* geraMatrizEsparsa(int tamanhoMatriz);

// Função necessária para adicionar uma dependência
void insereDependencia(matrizEsparsa* matrizEsparsa, bool valor, int linha, int coluna);
// Funções necessárias pra inserir uma dependência
noListaPrimariaR* encontraNoListaPrimaria(matrizEsparsa* matrizEsparsa, int linha);
noListaSecundariaR* encontraNoListaSecundaria(noListaPrimariaR* noP, int coluna);

// Função que exclui uma tarefa de um fluxo
void excluiTarefa(matrizEsparsa* matrizEsparsa, int linha);

// Função que verifica se uma tarefa existe em um fluxo
bool tarefaExisteFluxo(matrizEsparsa* matrizEsparsa, int linha);

// Função que retorna o valor, dado uma posição
bool valorPosicao(matrizEsparsa* matrizEsparsa, int linha, int coluna);

// Função que imprime uma matriz de restrição
void imprimeMatrizEsparsa(matrizEsparsa* matrizEsparsa, int tamanhoMatriz);

//////////////////////////////////////////////////////////////////////////////

// Função responsável para adicionar o nó
void adicionaValor(matrizEsparsa* matrizEsparsa, int valor, int linha, int coluna);
// Funções necessárias para inserir um elemento
noListaPrimariaR* encontraNoListaPrimariaS(matrizEsparsa* matrizEsparsa, int linha);
noListaSecundariaR* encontraNoListaSecundariaS(noListaPrimariaR* noP, int coluna);
void insereElemento(noListaSecundariaR* noS, int valor);

// Verifica se elemento existe
bool existe(matrizEsparsa* matrizEsparsa, int linha, int coluna);
// Função necessária para verificar se elemento existe
bool procuraColuna(noListaPrimariaR* noP, int coluna);