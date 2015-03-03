# include "csparse.h"
using namespace std;

cs* geraMatrizTransicoes(int** matrizAtivacao, int** matrizDesativacao, int totalAcoes);

cs* geraMatrizAtivacao(int** matrizAtivacao, int totalAcoes);
cs* geraMatrizAtivacao(int** matrizAtivacao, cs* matrizTransicoes, int totalAcoes);

cs* geraMatrizDesativacao(int** matrizDesativacao, int totalAcoes);
cs* geraMatrizDesativacao(int** matrizDesativacao, cs* matrizTransicoes, int totalAcoes);