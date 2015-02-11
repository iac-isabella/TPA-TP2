/*
 * global.h
 *
 *  Created on: 07/07/2014
 *      Author: mateus
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_
#include <stdlib.h>
#include<string.h>
#include <math.h>
#include "csparse.h"
#define MSG1_ERROLSTE "Valores de estados acima do limite do sistema de transição\n"
#define MSG_ERRO_EXPRINV "Expressão de processo inválida\n"
#define TRUE 1
#define FALSE 0
#define OPERADOR 1
#define ATIVIDADE 2
#define SUBPROCESSO 3
#define SEP 4
#define MAX_TAREFAS 32
#define TS_1 1
#define TAREFAINEXISTENTE -1
#define DPARALELO '+'
#define DEXCLUSIVO '*'
typedef unsigned int Estado;
 struct t{
	   unsigned  int id;
	   char  nome;
	   char  nomecompleto[30];
         };

 typedef struct t Tarefa;
 typedef struct nodoLE{
 	       Estado e;
 	       struct nodoLE *prox;
          } NodoLE;
 typedef NodoLE *ListaDeEstados;
 typedef struct nodo {
                 char termo;
                 int tipo;
                 struct nodo *esq,*dir;
                 } Nodo;
 typedef  Nodo *Arvore;
 typedef struct noseq{
 	               char nome;
 	               struct noseq *prox;
                   } NodoSeq;
 typedef NodoSeq *SubProcSeq;  // subprocesso sequencial

  typedef struct {
 	         SubProcSeq sps[MAX_TAREFAS];
 	         short nsps;
  }TabSubProc;
  typedef struct {short nl,nc;
                    short tab[MAX_TAREFAS][MAX_TAREFAS];
   }TabExclusao;

 typedef struct { Arvore ptree; // árvore de estrutura do processo
                  Tarefa *t; // vetor de tarefas do processo
                  TabSubProc *tsub;
                  TabExclusao *tabx;
                  short nt;


 } Processo;
 typedef struct {
 	cs *mtrans; // matriz onde serão representadas as transições entre os estados.
 	unsigned ntarefas;
 } STrans;// sistema de transições



  // estado.h
Estado proxEstado(Estado e, Tarefa *t);
void  imprimeEstado(Estado e, unsigned nt);
char *  eBinario(Estado e, unsigned nt);
// listadeestado.h
void insereEstado(ListaDeEstados l, Estado e); // imprime a representação binária do estado
ListaDeEstados  merge(ListaDeEstados l, ListaDeEstados m); // junta l com m sem repetições
ListaDeEstados * exclui(ListaDeEstados l, ListaDeEstados m); // exclui m de l
unsigned estaEm(ListaDeEstados l, Estado e );
void inicializaLista(ListaDeEstados *l);
void insereNaLista(ListaDeEstados *l, Estado e);
void removedaLista(ListaDeEstados l);
void imprimeLista(ListaDeEstados l);
// processtree.h
Arvore criaNodo(char);
char * geradora(char *expr, Arvore *a);
int tipoDoTermo(char termo);
void printnodo(Arvore nodo);
void imprime (Arvore a);
int validaExpr(char *expr);
int geraProcesso(char *expr,Processo *p);

// subprocessos
inicializaTabSubProc(TabSubProc * tsp);
char criaSubProcSeq(char *seq,TabSubProc * tsp);
char * comprimeSubProcSequenciais(char *expr, TabSubProc *tsp);
int imprimeTabSubProc(TabSubProc *tsp);
int imprimeSubProc(SubProcSeq sp);
int existeViolacaoDeDependencia(Estado e, Tarefa t, Processo *p);
int checaDependencia(char r,char t,TabSubProc *tsp);
void geraEstadosProcSeq(STrans *s, ListaDeEstados *eo, ListaDeEstados *eg, TabExclusao tabx, Processo *p, char procSec);
// sistemaDetransicoes.h
void inicializaSTrans(STrans *s, unsigned ntarefas);
int insereTrans(STrans *s, Estado o, Estado d);
/* cria um sistema de transições para n tarefas paralelas*/
void criaSTransDenso(STrans *s, unsigned ntarefas);
/*
 * Gera o sistema de transições equivalente a uma árvore de processo de negócio
 *
 * */
void geraStrans(STrans *s, Processo *p);
void imprimeSTrans(STrans *s);
void imprimeProcesso(Processo *p);
short obtemIndiceTarefa(Processo *p, char nome);
/* Gera a lista de estados novos originados de uma lista de estados origem e com a execução de uma tarefa.
 *
 */
void geraEstados(ListaDeEstados *g, ListaDeEstados o, Tarefa t, Processo *p,TabExclusao tabx);
short tarefaExecutada(Estado e, Tarefa t, unsigned nt);
/*
 * registras as transições geradas pela execução da tarefa t a partir do conjunto de estados origem eo.
 *
 */
void registraNovasTransicoes(STrans *s,ListaDeEstados eo,Tarefa t, Processo *p, TabExclusao tabx);
void obtemTarefasDeUmaArvore(Arvore a, char *vt, short *nt);
void montaTabelaExclusao(Processo *p, Arvore a,Arvore b, TabExclusao *tabx);
void atualizaTabelaExclusao(Processo *p, Arvore a,Arvore b, TabExclusao *tabx);
void imprimeTabelaDeExclusao(TabExclusao *tabx);
void copiaTabExclusao(TabExclusao *tabd,TabExclusao *tabo);
int saoExclusivas(short a, short b, TabExclusao tabx);
int possuiTarefaExclusiva(Estado eo,  Tarefa t, TabExclusao tabx);
void geraTraces(STrans *s, Processo *p, Arvore a, char pai, ListaDeEstados *eo, ListaDeEstados *eg, TabExclusao tabxPai);

#endif /* GLOBAL_H_ */
