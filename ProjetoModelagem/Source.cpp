# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>

# include "csparse.h"

int main(void)
{
	int i;
	int m;
	cs *T;

	printf("\n");
	printf("Inicio de exemplo\n");
	
	// Tamanho da matriz
	m = 0;

	// Criando matriz esparsa
	T = cs_spalloc(m, m, m, 1, 1);
	
	// Inserindo valores
	for (i = 0; i < 10; i++)
	{
		cs_entry(T, i, i, i);
	}
	
	// Imprimindo matriz
	cs_print(T);
	
	// Clareando matriz
	cs_spfree(T);

	// Fim
	printf("\n");
	printf("Fim\n");
	system("PAUSE");
	return (0);
}