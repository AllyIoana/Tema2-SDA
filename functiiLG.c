/* PATRASCU Ioana-Alexandra - grupa 314CB */
/*---operatii de baza pentru lista simplu inlantuita generica---*/
#include "tlg.h"
#include "task.h"

TLG Aloc_CelulaG(void* x)
{
	TLG aux;
  	aux = (TLG)malloc(sizeof(TCelulaG));
   	if(!aux) return NULL;
   	
	aux->info = x;
	aux->urm = NULL;
	aux->prec = NULL;
	return aux;
}

int Add_LastLG(TLG* list, void* elem)
{
	TLG aux = Aloc_CelulaG(elem);
	if(!aux) 
	    return 0;
	if(*list == NULL) /* la adaugarea primului element */
	{
		*list = aux;
		(*list)->urm = aux;
		(*list)->prec = aux;
		return 1;
	}
	/* lista nu e vida */
	((*list)->prec)->urm = aux;
	aux->urm = *list;
	aux->prec = (*list)->prec;
	(*list)->prec = aux;

	return 1;
}

Task* Extract(TLG *coada)
{
	if(*coada) {
		TLG start = *coada;
		Task* aux = start->info;
		if((*coada) == (*coada)->prec) /* un  singur element */
		{
			free(*coada);
			*coada = NULL;
			return aux;
		}
		TLG end = (*coada)->prec;
		end->urm = start->urm;
		(*coada)->urm->prec = end;
		*coada = (*coada)->urm;
		free(start);
		return aux;
	}
	return NULL;
}

Thread* Pop(TLG *stiva)
{
	if(*stiva)
	{
		TLG end = (*stiva)->prec;
		Thread* aux = end->info;
		if((*stiva) == (*stiva)->prec) /* un singur element */
		{
			free(*stiva);
			*stiva = NULL;
			return aux;
		}
		end->prec->urm = *stiva;
		(*stiva)->prec = end->prec;
		free(end);
		return aux;
	}
	return NULL;
}

void DistrugereCoada(TLG* coada)
{
	Task* task;
	while(*coada != NULL)
	{
		task = Extract(coada);
		free(task);
	}
	free(coada);
}

void DistrugereStiva(TLG* stiva)
{
	while(*stiva != NULL)
		Pop(stiva);
}
