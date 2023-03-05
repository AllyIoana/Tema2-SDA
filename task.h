/* PATRASCU Ioana-Alexandra - grupa 314CB */
#include <stdio.h>
#include "tlg.h"
#define MaxTask 32767
#define MaxThread 127

typedef struct
{
    char ID; /* porneste de la 1, N < 128 */
} Thread;

typedef struct 
{
    short ID; /* [1-32767], cel mai mic posibil mereu */
    Thread thread; /* se atribuie automat */
    char priority; /* [0-127], dat la creare */
    unsigned long time; /* timpul de executie */
} Task;

Task* Extract(TLG *coada); /* extragem primul task dintr-o coada */
Thread* Pop(TLG *stiva); /* extragem ultimul thread din stiva */

int add_waiting(TLG *waiting, Task* task); /* A: adauga un task in coada de asteptare */
int add_tasks(TLG *waiting, FILE* output, int n, unsigned long time,
              char priority, int *aparTask); /* A: creeaza task-uri */
int get_task(TLG *coada, FILE *output, char *type, short ID); /* B: aflam informatii despre un task */
int get_thread(TLG *stiva, char IDthread); /* C: verificam daca un thread este folosit */
void print_thread(TLG *running, char IDthread, FILE *output); /* C: aflam informatii despre un thread */
void run_waiting(TLG *waiting, TLG *running, TLG *pool,
                 unsigned long time, unsigned long *totalTime);
                 