struct matrizEsparsa;
struct noListaPrimariaR;
struct noListaSecundariaR;

// Fun��o que cria uma matriz de restri��o
matrizEsparsa* geraMatrizEsparsa(int tamanhoMatriz);

// Fun��o necess�ria para adicionar uma depend�ncia
void insereDependencia(matrizEsparsa* matrizEsparsa, bool valor, int linha, int coluna);
// Fun��es necess�rias pra inserir uma depend�ncia
noListaPrimariaR* encontraNoListaPrimaria(matrizEsparsa* matrizEsparsa, int linha);
noListaSecundariaR* encontraNoListaSecundaria(noListaPrimariaR* noP, int coluna);

// Fun��o que exclui uma tarefa de um fluxo
void excluiTarefa(matrizEsparsa* matrizEsparsa, int linha);

// Fun��o que verifica se uma tarefa existe em um fluxo
bool tarefaExisteFluxo(matrizEsparsa* matrizEsparsa, int linha);

// Fun��o que retorna o valor, dado uma posi��o
bool valorPosicao(matrizEsparsa* matrizEsparsa, int linha, int coluna);

// Fun��o que imprime uma matriz de restri��o
void imprimeMatrizEsparsa(matrizEsparsa* matrizEsparsa, int tamanhoMatriz);

//////////////////////////////////////////////////////////////////////////////

// Fun��o respons�vel para adicionar o n�
void adicionaValor(matrizEsparsa* matrizEsparsa, int valor, int linha, int coluna);
// Fun��es necess�rias para inserir um elemento
noListaPrimariaR* encontraNoListaPrimariaS(matrizEsparsa* matrizEsparsa, int linha);
noListaSecundariaR* encontraNoListaSecundariaS(noListaPrimariaR* noP, int coluna);
void insereElemento(noListaSecundariaR* noS, int valor);

// Verifica se elemento existe
bool existe(matrizEsparsa* matrizEsparsa, int linha, int coluna);
// Fun��o necess�ria para verificar se elemento existe
bool procuraColuna(noListaPrimariaR* noP, int coluna);