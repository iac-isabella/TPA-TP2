/*
 * strans.c
 *
 *  Created on: 07/07/2014
 *      Author: mateus
 */
#include "global.h"

void imprimeEstado(Estado e,unsigned nt){
	unsigned i;
	unsigned mask = 1<<31;
//	printf("%10u=",e);
	for(i=0;i<32;i++){
        if (i>=32-nt)
		   putchar(e & mask ?'1' : '0');
		e <<= 1;
	}
//	putchar('\n');
}
/* ebinário (estadoBinário): retorna as string binária correspondente a um estado dependente de nt tarefas */
char * eBinario(Estado e,unsigned nt){
	unsigned i,k;
	char *bin = malloc(nt+1);
	unsigned mask = 1<<31;
	k=0;
	for(i=0;i<32;i++){
        if (i>=32-nt){
		   bin[k]=e & mask ?'1' : '0';
		   k++;
        }

		e <<= 1;
	}
	//k++;
	 bin[k]='\0';
return bin;
}
Estado proxEstado(Estado origem, Tarefa *t){
	unsigned tbin=0;
	tbin=pow(2,t->id-1);
	printf("%d\n",tbin);
	return origem|tbin;
}


// lista de estados
/*
 * estaEm - verifica se um estado está presente em uma lista de estados
 */
unsigned estaEm(ListaDeEstados l, Estado e ){
	unsigned i=0;
	ListaDeEstados p;
	p=l;
	while(p!=NULL){
		if (p->e==e){
			return TRUE;

		}
		p=p->prox;
	}
	return FALSE;
}
/*
 * inicializa lista de estados
 */
void inicializaLista(ListaDeEstados *l){
	*l=NULL;
}
/*
 * insere um estado e em uma lista de estados l
 */
void insereNaLista(ListaDeEstados *l, Estado e){
	ListaDeEstados novoNodo;
	novoNodo=malloc(sizeof(NodoLE));
	novoNodo->e=e;
	novoNodo->prox=*l;
	*l=novoNodo;

}

void removedaLista(ListaDeEstados l){

}
/* imprime uma lista de estados do início para o fim.
 *
 */
void imprimeLista(ListaDeEstados l){
 ListaDeEstados p;
 p=l;
 printf("{");
 while(p!=NULL){
	 imprimeEstado(p->e,5);
	 p=p->prox;
	 printf(",");
 }
 printf("}");
}

ListaDeEstados   merge(ListaDeEstados l, ListaDeEstados m){
	// junta l com m sem repetições

	ListaDeEstados p=NULL, novoNodo;
	if (l!=NULL){
	  novoNodo=malloc(sizeof(NodoLE));
	  p=novoNodo;

	  while (l!=NULL){
		 *novoNodo=*l;
		 novoNodo=malloc(sizeof(NodoLE));
		 l=l->prox;

	  }
	}
	if (m!=NULL){
		while(m){
		  if(estaEm(p,m->e)==FALSE){
			  insereNaLista(&p,m->e);
		  }
		  m=m->prox;

		}
	}
return p;

}
ListaDeEstados * exclui(ListaDeEstados l, ListaDeEstados m){
	// exclui m de l
}
// process tree

void printnodo(Arvore nodo){
  printf("termo: %c\n",nodo->termo);
}

/*
 * TODO: uso do valor de 0 a 9 para subprocesso limita subprocessos a um numero de 10.
 *
 */
int tipoDoTermo(char termo) {
  if ((termo>='A') && (termo<='Z')){
       return ATIVIDADE;
  }
  else
    if ((termo == '+') || (termo == '*')) {
       return OPERADOR;
   }
   else
	   if ((termo>='0') && (termo<='9')){
		   return SUBPROCESSO;
	   } else {

	       return SEP;
	   }
}

Arvore criaNodo(char termo){
  Arvore nodo;
  nodo = malloc(sizeof(Nodo));
  nodo->termo=termo;
  nodo->esq=NULL;
  nodo->dir=NULL;
  nodo->tipo=tipoDoTermo(termo);
  return nodo;
}

char *getnexpr(const char *expr){
 char *nexpr;
    nexpr = malloc((strlen(expr))*sizeof(char));
    strncpy(nexpr, ++expr,strlen(expr));
    return nexpr;
}
/* substitui sequencias de atividades por um único símbolo na tarefa e gera o mapeamento desse símbolo na estrutura do processo.
 * */


// subprocessos
inicializaTabSubProc(TabSubProc * tsp){
	int i;
		for(i=0;i<MAX_TAREFAS;i++){
		tsp->sps[i]=NULL;

	}
	tsp->nsps=0;
}
char criaSubProcSeq(char *seq,TabSubProc *tsp){
	int i;
	NodoSeq *nseq;
	SubProcSeq *sp;
	char buff[2];

	sp = &tsp->sps[tsp->nsps];
    printf("Sequencia de subprocesso: %s\n", seq);
	for(i=0;i<strlen(seq);i++){
		   nseq = malloc(sizeof(NodoSeq));
           nseq->prox=NULL;
           nseq->nome=seq[i];
		   *sp=nseq;
		   sp=&((*sp)->prox);
	}
	tsp->nsps++;
	//sprintf(buff,"%c\0",tsp->nsps);
    return (char) 48+(tsp->nsps-1);
}
imprimeSubProc(SubProcSeq sp){
	while(sp){
		printf("%c ",sp->nome);
		sp=sp->prox;
	}
	printf("\n");
}
imprimeTabSubProc(TabSubProc *tsp){
	int i;
	for(i=0;i<tsp->nsps;i++){
		imprimeSubProc(tsp->sps[i]);
	}


}
char * comprimeSubProcSequenciais(char *expr, TabSubProc *tsp){
	int i,j,k,l,n,m;
	char indProc;
	char *eaux,  seq[MAX_TAREFAS];
	eaux = malloc(MAX_TAREFAS);
    strcpy(eaux,expr); // faz uma copia da expressao original
    n=strlen(expr); // guarda o tamanho da expressão original.
    i=0;
    while(i<n) { // percorre todos os elementos de expr
      j=i;
       while(tipoDoTermo(eaux[j])==ATIVIDADE){ //procura um subprocesso sequencial
    	   j++;
       }
       if(j>i+1) { /* se encontrou um subprocesso seq (mais de uma atividade em sequencia)
                      pego o conjunto de atividades que está entre i e j-1 */
    	   strncpy(seq,&eaux[i],j-i); // cria a string so supprocesso sequencial
    	   seq[j-i]='\0';
    	   printf("sequencia no comprime sub proc: %s\n", seq);
    	   indProc=(char) criaSubProcSeq(seq,tsp); // crio o supprocesso equivalente
    	   /* substituo a sequencia pelo indice retornado por criasubprocseq na  exprc */

    	   eaux[i]=indProc;
    	   printf("indProc: %c\n",(char) indProc);
    	   l=i+1;
    	   for(k=j;eaux[k]!='\0';k++){
    		   eaux[l]=eaux[k];
    		   l++;
    	   }
    	   eaux[l]='\0';
    	   i=j;
       }
       else {
    	   i++;
       }

    }
    printf("\n imprimindo eaux:%s\n", eaux);
    return eaux;
}
/* retorna verdadeiro se a tarefa r deve executar antes  da tarefa s em pelo menos
 * um processo sequencial. Ou seja existe uma dependencia de s para com r
 */
int checaDependencia(char r, char s, TabSubProc *tsp){
	int i, achour, achous;
	SubProcSeq sps;
	for(i=0;i<tsp->nsps;i++){
		achour=FALSE;
		achous=FALSE;
		sps = tsp->sps[i];
		while(sps!=NULL){
			if(sps->nome==r){
				achour=TRUE;
				break;
			}
			sps=sps->prox;
		}
		while(sps!=NULL){
		  if(sps->nome==s){
			 achous=TRUE;
			 break;
		  }
		  sps=sps->prox;

		}
		if (achour && achous){
			return TRUE;
		}
	}
	return FALSE;
}

/*checa regra de dependência.
 * Verifica se um estado há alguma tarefa executada que não pode presceder uma tarefa t
 * Usa-se esta função para que não se gere um novo estado que fira uma regra de precedência de acordo com uma
 *  tabela de subprocessos sequenciais
 *  retorna 0 se não há dependência ou o número da tarefa que viola a dependência.
 */
int existeViolacaoDeDependencia(Estado e, Tarefa t, Processo *p){
	char *ebin,r,s;
	int i,k;
		ebin = eBinario(e,p->nt);
		s=t.nome;

		//printf("valor de e e ebin: %d -  %s\n",e, ebin);
    for(i=0;i<p->nt;i++){
    	r=p->t[i].nome;
    	if((ebin[p->nt-(i+1)]=='0') && (r!=s)){
    		if(checaDependencia(r,s,p->tsub)==TRUE){
    			return TRUE;
    		}
    	}
    }
    return FALSE;

}
char * geradora( char *expr, Arvore *a){
  char t;
  int ttermo;

  while((tipoDoTermo(expr[0])==SEP) && (expr[0]!='\0')){
    expr=getnexpr(expr);
  }
  t = expr[0];
  ttermo = tipoDoTermo(t);
  printf("termo processado: %c\n", t);
  if ((ttermo == OPERADOR) || (ttermo == ATIVIDADE) || (ttermo== SUBPROCESSO) ){
     *a=criaNodo(t);
  }
   if(ttermo==OPERADOR) {
          expr=getnexpr(expr);
          expr =geradora(expr,(&(*a)->esq));
          // printf("\n%s\n",expr);
          expr=getnexpr(expr);
          expr=geradora(expr,(&(*a)->dir));
     }

 return expr;
}
void imprime (Arvore a) {
    if (a == NULL) return;
    printnodo(a);
    imprime(a->esq);
    imprime(a->dir);
}

void inicializaSTrans(STrans *s, unsigned ntarefas){
	s->ntarefas=ntarefas;
	 s->mtrans = cs_spalloc((unsigned)pow(2,s->ntarefas),(unsigned) pow(2,s->ntarefas), 1 ,1, 1);

}
/*insere uma transição do estado origem o para o estado destino d*/
int insereTrans(STrans *s, Estado o, Estado d){
	if ((o<s->mtrans->n) && (d<s->mtrans->m)) {
	    cs_entry(s->mtrans,o,d,TS_1);
	}
	else {
		printf(MSG1_ERROLSTE);
		return 0;
	}

}
/* cria um sistema de transições para n tarefas paralelas*/
void criaSTransDenso(STrans *s, unsigned ntarefas){
	unsigned i,j;
	inicializaSTrans(s,ntarefas);
	printf("nzmax: %d, nz: %d, n: %d, m: %d \n", s->mtrans->nzmax,s->mtrans->nz, s->mtrans->n,s->mtrans->m);
	for(i=0;i<pow(2,ntarefas);i++){
		for (j=i;j<pow(2,ntarefas);j++){
              insereTrans(s,i,j);

		}
	}
	for(i=0;i<pow(2,ntarefas);i++){
			for (j=i;j<pow(2,ntarefas);j++){
				updateEntry(s->mtrans, i,j, 1);
			}
		}
	  printf("nzmax: %d, nz: %d, n: %d, m: %d \n", s->mtrans->nzmax,s->mtrans->nz, s->mtrans->n,s->mtrans->m );
}
/**
 * Imprime o sistema de transições no formato matricial
 */
void imprimeSTrans(STrans *s){
	int i,k;
	printf("   ",i);
	for ( i = 0; i < s->mtrans->m; i++ )
		 printf("%2d ",i);


	 printf("\n");
	 for ( i = 0; i < s->mtrans->n; i++ ){
		             printf("%2d ",i);
		           	 for (k=0;k<s->mtrans->m;k++)
		       	  {

		           		printf("%2g ",getEntry(s->mtrans, i,k));
		       	  }

		          printf("\n");
		        }

	//cs_printMformat(s->mtrans,0);
}

/*
 * Gera o sistema de transições equivalente a uma árvore de processo de negócio
 *
 * */
int validaExpr(char *expr){
	return 1;

}
int geraProcesso(char *expr,Processo *p)
{
    int i, ct;
    char atv[500];
	char *exprComprimida;
	if (validaExpr(expr)==FALSE){
		printf(MSG_ERRO_EXPRINV);
		return FALSE;
	}
    i=0;
    ct=0;
    /* determina as tarefas do processo e guarda as tarefas em um vetor de caracteres*/

    while(i<strlen(expr)){
    	if(tipoDoTermo(expr[i])==ATIVIDADE) {
    		atv[ct]=expr[i];
    		ct++;
    	}
    	i++;
    }
    /*aloca o espaco no processo p e cria uma tarefa para cada tarefa obtida na expressão
     * */
    p->nt=ct;

    p->t=malloc(ct*sizeof(Tarefa));
    printf("ok1\n");

    for(i=0;i<ct;i++){
    	p->t[i].id=i+1;
    	p->t[i].nome=atv[i];
    }
    printf("ok2\n");
     p->tsub=malloc(sizeof(TabSubProc));
    /*
     *Comprime os processos sequenciais
     *
     */
    inicializaTabSubProc(p->tsub);
  	exprComprimida=comprimeSubProcSequenciais(expr, p->tsub);
    geradora(exprComprimida,&(p->ptree));
    }
void imprimeProcesso(Processo *p){
	int i;
	i=0;
	printf("Imprimindo um processo de negocio\n");
	printf("Tarefas - nome - id\n");
	while(i<p->nt){
		printf(" %d - %c\n", p->t[i].id,p->t[i].nome);
		i++;
	}
	printf("Arvore de estrutura\n");
	imprime(p->ptree);
}
short obtemIndiceTarefa(Processo *p, char nome){
	int i=0;
	while(i<p->nt){
		if(p->t[i].nome==nome){
			return i;

		}
		i++;
	}
	return TAREFAINEXISTENTE;
}
/* Gera a lista de estados novos originados de uma lista de estados origem e com a execução de uma tarefa.
 *
 */
void geraEstados(ListaDeEstados *g, ListaDeEstados o, Tarefa t, Processo *p, TabExclusao tabx){
	Estado ne;
	inicializaLista(g);
	while(o){
		if (possuiTarefaExclusiva(o->e,t,tabx)==FALSE){
			if (existeViolacaoDeDependencia(o->e, t, p)==FALSE){
		      ne= proxEstado(o->e,&t);
		      insereNaLista(g,ne);
			}
		}
		o=o->prox;
	}
}
short tarefaExecutada(Estado e, Tarefa t, unsigned nt){
	char *ebin;
	ebin=eBinario(e, nt);
	return (ebin[nt-t.id]== '1');

}
/*
 * registras as transições geradas pela execução da tarefa t a partir do conjunto de estados origem eo.
 *
 */
void registraNovasTransicoes(STrans *s,ListaDeEstados eo,Tarefa t, Processo *p, TabExclusao tabx){
	Estado d;

	while(eo){
		if(tarefaExecutada(eo->e,t,s->ntarefas)==FALSE){
			if (possuiTarefaExclusiva(eo->e,t,tabx)==FALSE){
						if (existeViolacaoDeDependencia(eo->e, t, p)==FALSE){

		       d = proxEstado(eo->e,&t);
			   insereTrans(s,eo->e,d);
			}
		}
	}
			 eo=eo->prox;
	}
}

void geraStrans(STrans *s, Processo *p){
ListaDeEstados eo, eg;
TabExclusao tabx;
inicializaTabExclusao(p,&tabx);
inicializaLista(&eo);
inicializaLista(&eg);
insereNaLista(&eo,0);

geraTraces(s,p,p->ptree,'!',&eo,&eg,tabx);
imprimeSTrans(s);
//geraEstados(&eg,eo,p->t[0]);
//imprimeLista(eg);
}

 void obtemTarefasDeUmaArvore(Arvore a, char *vt, short *nt){
	 if (a!=NULL){
	 if ((tipoDoTermo(a->termo)== ATIVIDADE) || (tipoDoTermo(a->termo)== SUBPROCESSO)){
		 vt[*nt]=a->termo;
		 (*nt)++;
	 }
	 else {
	 obtemTarefasDeUmaArvore(a->esq,vt,nt);
	 obtemTarefasDeUmaArvore(a->dir,vt,nt);
	 }
	 }
 }
 /* monto a tabela de exclusão entre duas arvores. toa tarefa presente na árvore esquerda é exclusiva para toda tarefa da árvore direita
  * Essa função será usada para indicar tarefas exclusivas em uma bifurcação ou exclusiva da árvores (*)*/
void inicializaTabExclusao(Processo *p,TabExclusao *tabx){
	int i,j;
	tabx->nl=p->nt;
	tabx->nc=p->nt;
	 for(i=0;i<MAX_TAREFAS;i++){
			 for(j=0;j<MAX_TAREFAS;j++){
				 tabx->tab[i][j]=FALSE;
			 }
		 }

}
void montaTabelaExclusao(Processo *p, Arvore a,Arvore b, TabExclusao *tabx){
	char vt_esq[MAX_TAREFAS], vt_dir[MAX_TAREFAS];
	short nt_esq=0,nt_dir=0, i,j,tdir[MAX_TAREFAS],tesq[MAX_TAREFAS],x,y,r,k;
	 obtemTarefasDeUmaArvore(a,vt_esq,&nt_esq);
	 obtemTarefasDeUmaArvore(b,vt_dir,&nt_dir);
	 for(i=0;i<MAX_TAREFAS;i++){
		 for(j=0;j<MAX_TAREFAS;j++){
			 tabx->tab[i][j]=FALSE;
		 }
	 }
	 tabx->nl=p->nt;
	 tabx->nc=p->nt;
	 for(i=0;i<nt_esq;i++){
		 /* verifico se a atividade é um subprocesso sequencial.
		  * Nesse caso obtenho a lista desse subprocesso
		  */
		 if(tipoDoTermo(vt_esq[i])==SUBPROCESSO){

		 }
		 else {
			 x=1;
		    tesq[0]= obtemIndiceTarefa(p,vt_esq[i]);
		 }
		  for(j=0;j<nt_dir;j++){
			  if(tipoDoTermo(vt_esq[i])==SUBPROCESSO){

			 		 }
			 		 else {
			 			 y=1;
			 			tdir[0]= obtemIndiceTarefa(p,vt_dir[j]);;
			 		 }
			  for(k=0;k<x;k++){
				  for (r=0;r<y;r++)
			  		  tabx->tab[tesq[k]][tdir[r]]=TRUE;
			  }
		  }
	 }

}
void atualizaTabelaExclusao(Processo *p, Arvore a,Arvore b, TabExclusao *tabx){
	char vt_esq[MAX_TAREFAS], vt_dir[MAX_TAREFAS];
	short nt_esq=0,nt_dir=0, i,j,tdir[MAX_TAREFAS],tesq[MAX_TAREFAS],x,y,r,k,l, indProc;
	SubProcSeq sps;
	char buff[2];

	 obtemTarefasDeUmaArvore(a,vt_esq,&nt_esq);
	 obtemTarefasDeUmaArvore(b,vt_dir,&nt_dir);
	 	 for(i=0;i<nt_esq;i++){
	 		/* verifico se a atividade é um subprocesso sequencial.
	 				  * Nesse caso obtenho a lista desse subprocesso
	 				  */
	 				 if(tipoDoTermo(vt_esq[i])==SUBPROCESSO){
	 					    sprintf(buff,"%c",vt_esq[i]);
	 						indProc = atoi(buff);
	 						sps = p->tsub->sps[indProc];
	 						x=0;
	 						while(sps){
	 							tesq[x]= obtemIndiceTarefa(p,sps->nome);
	 							x++;
	 							sps=sps->prox;
	 						}
	 				 }
	 				 else {
	 					 x=1;
	 				    tesq[0]= obtemIndiceTarefa(p,vt_esq[i]);
	 				 }
	 				  for(j=0;j<nt_dir;j++){
	 					  if(tipoDoTermo(vt_dir[j])==SUBPROCESSO){
	 						 sprintf(buff,"%c",vt_dir[j]);
	 						 indProc = atoi(buff);
	 						 sps = p->tsub->sps[indProc];
	 						 y=0;
	 						 while(sps){
	 						 	tdir[y]= obtemIndiceTarefa(p,sps->nome);
	 						 	y++;
	 						 	sps=sps->prox;
	 						}
	 					}
	 					 		 else {
	 					 			 y=1;
	 					 			tdir[0]= obtemIndiceTarefa(p,vt_dir[j]);;
	 					 		 }
	 					  for(k=0;k<x;k++){
	 						  for (r=0;r<y;r++)
	 					  		  tabx->tab[tesq[k]][tdir[r]]=TRUE;
	 					  }
	 				  }
	 			 }
}
/*
 * Faz uma copia de uma tabela de exclusao
 *
 */
void copiaTabExclusao(TabExclusao *tabd,TabExclusao *tabo){
	int i,j;
	 for(i=0;i<tabo->nl;i++){
			 for(j=0;j<tabo->nc;j++){
				 tabd->tab[i][j]=tabo->tab[i][j];
			 }
		 }
		 tabd->nl=tabo->nl;
		 tabd->nc=tabo->nc;

}
/*
 * verifica se duas tarefas são exclusivas segundo a tabela de exclusao tabx
 *
 */
int saoExclusivas(short a, short b, TabExclusao tabx){
	return(tabx.tab[a][b] || tabx.tab[b][a]);

}
/*
 * Imprime uma tabela de exclusão.
 */
void imprimeTabelaDeExclusao(TabExclusao *tabx){
	short i,j;
	 for(i=0;i<tabx->nl;i++){
			 for(j=0;j<tabx->nc;j++){
				 printf("%d ",tabx->tab[i][j]);
			 }
			 printf("\n");
		 }


}
/*
 * Verifica se um estado possui uma tarefa executada exclusiva à tarefa t
 *
 * */

possuiTarefaExclusiva(Estado eo, Tarefa t, TabExclusao tabx){
	char *ebin;
	int i,s;

	ebin=eBinario(eo, tabx.nl);
	s = strlen(ebin);
	for(i=0;i<strlen(ebin);i++){
		if (ebin[i]=='1'){
		  if( saoExclusivas(s-(i+1),t.id-1, tabx)){
			  return TRUE;
		  }
		}
	}
	return FALSE;

}
/*
 * gera o sistema de transições equivalente a um processo p e uma árvore de estado desse processo.
 * a árvore é passada separadamente mas faz parte do processo.
 * Cada execução de geratrace ao encontrar um nodo Atividade na arvore gera os novos estados oconsiderando
 *  uma lista de estados origem (eo). Os novos estados são gerados e inseridos numa lista auxiliar eg e na matriz
 *  de transições do sistema STrans.
 *
 */
void geraEstadosProcSeq(STrans *s, ListaDeEstados *eo, ListaDeEstados *eg, TabExclusao tabx, Processo *p, char procSec){
	int indProc,i;
	SubProcSeq sps;
	ListaDeEstados eaux;
	char buff[2];
	sprintf(buff,"%c",procSec);
	indProc = atoi(buff);
	sps = p->tsub->sps[indProc];

	while(sps){
	inicializaLista(&eaux);
		i= obtemIndiceTarefa(p, sps->nome);
	    geraEstados(&eaux,*eo,p->t[i], p, tabx);
	    *eg=merge(*eg,eaux);
	    registraNovasTransicoes(s,*eo,p->t[i],p, tabx);
	    *eo=merge(*eo,eaux);
	    sps=sps->prox;
	}

}
void geraTraces(STrans *s, Processo *p, Arvore a, char pai, ListaDeEstados *eo, ListaDeEstados *eg, TabExclusao tabxPai){
	short i;
	  TabExclusao tabx;
      ListaDeEstados eaux;
	  inicializaLista(&eaux);
	  copiaTabExclusao(&tabx,&tabxPai);
   switch  (tipoDoTermo(a->termo)){


   case ATIVIDADE:
          i= obtemIndiceTarefa(p, a->termo);
           geraEstados(&eaux,*eo,p->t[i], p, tabx);
           *eg=merge(*eg,eaux);
           registraNovasTransicoes(s,*eo,p->t[i], p, tabx);
           /* se o no pai da árvore é um +, adiciono os estado gerado na lista de estado origem */
           if(pai==DPARALELO){
        	   *eo = merge(*eo,*eg);
        	   inicializaLista(eg);
           }

      break;
   case SUBPROCESSO:
	   geraEstadosProcSeq(s, eo, eg, tabx, p, a->termo);
	   break;

   case OPERADOR:
	   if(a->termo==DEXCLUSIVO){
		   /* monto a tabela de exclusao */
		   printf("\n Tabela de exclusao atualizada: \n");
		   atualizaTabelaExclusao(p,a->esq,a->dir,&tabx);
		   imprimeTabelaDeExclusao(&tabx);
	   }
	   geraTraces(s,p,a->esq,a->termo,eo,eg,tabx);
	   geraTraces(s,p,a->dir,a->termo,eo,eg,tabx);
	   if(pai==DPARALELO){
	   	   *eo = merge(*eo,*eg);
	   	   inicializaLista(eg);
	   }
	   if(a->termo==DPARALELO){
		   static int nr=0;
		   nr++;
		   //inicializaLista(eg);
		   printf("estados origem - nível %d\n",nr);
		   imprimeLista(*eo);
		   printf("estados gerados - nível %d\n",nr);
		   imprimeLista(*eg);
		   geraTraces(s,p,a->esq,a->termo,eo,eg,tabx);
	   }
	   break;
   }
}
/*


 void geraTraces(Fila *Q, Arvore a, char pai){

	switch(pai){
	case '!':
		insere(Q,0);
		if (a->tipo==OPERADOR){
		  geraTraces(Q,a->esq,a->termo);
		  geraTraces(Q,a->dir,a->termo);
		}
	case '+':
		while(nao esgotaram os estados origem não utilizados para gerar com o termo a){
		  if (a->tipo==ATIVIDADE){
     	 	geraEstados(a->termo, Q,pai);
		  } else {
			if (a->tipo==OPERADOR){
				 geraTraces(Q,a->esq,a->termo);
				 geraTraces(Q,a->dir,a->term
				 o);
			}
		  }
		}


	case '*':


	}
}
*/

