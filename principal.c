/*
 * principal.c
 *
 *  Created on: 06/07/2014
 *      Author: mateus
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "estado.h"
//#include "listadeestado.h"
//#include "processtree.h"
#include "csparse.h"
#include "global.h"
//#include "cs.h"
cs_printMformat(const cs *A,int brief);
double getEntry(cs *T, int r,int c);
/*void testeCSparse(){

	 cs *T;

	  printf ( "\n" );
	  printf ( "CS_DEMO1:\n" );
	  printf ( "  Demonstration of the CSPARSE package.\n" );

	//  Load the triplet matrix T from standard input.

	  T = cs_load ( stdin );

	//  Print T.

	  printf ( "T:\n" );
	  cs_print ( T, 0 );

}
*/
void testeArvore(){
	Arvore a;
	geradora("+(*(A;C);+(B;*(D;E)))\0",&a);
	imprime(a);
}
void testeListaEstados(){
	unsigned i;
	ListaDeEstados Eo,Eg,p;
	Estado x=2;
	// printf("\nbits e estados\n");
	  // imprimeEstado(x,5);
	  inicializaLista(&Eo);
	  inicializaLista(&Eg);
	  for (i=0;i<5;i++){
	  	insereNaLista(&Eo,i);

	  }
	  for (i=5
	  		;i<10;i++){
	  	insereNaLista(&Eg,i);

	  }

	  imprimeLista(Eo);
	  p=merge(Eo,Eg);
	  imprimeLista(p);
	  if(estaEm(Eo,4)){
	  	printf("\n O estado %s esta presente na Lista\n", eBinario(9,5));
	  }
}
 void testeCSparse2(){
	 cs *T;
	 int i,k;
	 T = cs_spalloc (1000000, 1000000, 1 ,1, 1);
	 csi p, j, m, n, nzmax, nz, *Ap, *Ai ;
	 double *Ax ;
	 nzmax = T->nzmax ; nz = T->nz ;
     n = T->n; m=T->m;



       for ( i = 0; i < 10; i++ )
    	 for (k=0;k<10;k++)
	  {
	    //cs_entry ( T, i, k, k*((i+k)%2));
         cs_entry ( T, i, k, k);
	  }
       cs_printMformat( T, 0 );
       nzmax = T->nzmax ; nz = T->nz ;
       n = T->n; m=T->m;
       Ap = T->p ; Ai = T->i ; Ax = T->x ;
       printf("nzmax: %d, nz: %d, n: %d, m: %d \n", nzmax,nz, n,m );
       for ( i = 0; i < 10; i++ ){
           	 for (k=0;k<10;k++)
       	  {
           		printf("%g ",getEntry(T, i,k));
       	  }

          printf("\n");
        }
 }


/* int cs_entry (cs *T, int i, int j, double x) {
     if (!T || (T->nz >= T->nzmax && !cs_sprealloc (T, 2*(T->nzmax)))) return(0);
     if (T->x) T->x [T->nz] = x ;
     T->i [T->nz] = i ;
     T->p [T->nz++] = j ;
     T->m = CS_MAX (T->m, i+1) ;
     T->n = CS_MAX (T->n, j+1) ;
     return (1) ;
 }
*/
void testeTarefas(){
	Estado e;
	STrans s;
	unsigned i,k;
	Tarefa t;
	t.id=5;
	t.nome="A";
	e= proxEstado(4,&t);
	imprimeEstado(4, 5);
	printf("\n");
	imprimeEstado(e, 5);
	//inicializaSTrans(&s, 5);
	criaSTransDenso(&s,3);

	imprimeSTrans(&s);
}
int testaTabSubProc(){
	TabSubProc tsp;
	inicializaTabSubProc(&tsp);
	char *ret;

	//ret=comprimeSubProcSequenciais("+(*(ASW;B);*(C;PRS))\0", &tsp);
	ret=comprimeSubProcSequenciais("+(*(QW;B);*(C;+(A;D))\0", &tsp);
	printf(ret);
	//criaSubProcSeq("abc\0",&tsp);
	//criaSubProcSeq("xhy\0",&tsp);
	//criaSubProcSeq("mateus\0",&tsp);
	//imprimeTabSubProc(&tsp);

}
void testeProcesso(){
	Processo p;
	STrans s;
	TabExclusao tabx;
	//geraProcesso("+(*(W;B);*(J;D))\0",&p);
	//geraProcesso("+(*(WQ;B);*(A;D))\0",&p);
	// geraProcesso("*(WQ;+(BA;Z))\0",&p);
	geraProcesso("*(W;+(Z;A))\0",&p);
	//geraProcesso("(+(*(WQ;ZK);*(Z;ABQ)\0",&p);
	imprimeProcesso(&p);
    inicializaSTrans(&s, p.nt);
	geraStrans(&s,&p);
}


  int main(){
	  //testeCSparse2();
//	  testeProcesso();
	 // testaTabSubProc();
	  testeTarefas();
  return 0;
  }
