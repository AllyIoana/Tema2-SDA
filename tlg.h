/* PATRASCU Ioana-Alexandra - grupa 314CB */
/*-- tlg.h --- LISTA SIMPLU INLANTUITA GENERICA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void* info;           /* adresa informatie */
  struct celulag *urm;   /* adresa urmatoarei celule */
  struct celulag *prec;   /* adresa celulei precedente */
} TCelulaG, *TLG; 	/* tipurile Celula, Lista generice */

/* functii lista generica */
TLG Aloc_CelulaG(void* x); /* alocare celula */
int Add_LastLG(TLG*, void*);  /* inserare la finalul cozii/stivei */
void DistrugereCoada(TLG* coada); /* distruge coada */
void DistrugereStiva(TLG* stiva); /* distruge stiva */

#endif