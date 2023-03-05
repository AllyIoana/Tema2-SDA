/* PATRASCU Ioana-Alexandra - grupa 314CB */
#include <stdio.h>
#include "task.h"
#include "tlg.h"

int add_waiting(TLG *waiting, Task *task)
{
    if (*waiting == NULL) //coada vida
        return Add_LastLG(waiting, task);

    Task *end = Extract(waiting);
    TLG *caux = malloc(sizeof(TLG)); /* coada auxiliara */
    *caux = NULL;

    /*-------Pas 1-------*/
    /* adaugam prioritatile mai mari */
    while (end->priority > task->priority)
    {
        Add_LastLG(caux, end);
        if (*waiting == NULL)
            break;
        end = Extract(waiting);
    }
    /* prioritate egala, timp mai mic */
    while (end->priority == task->priority && end->time < task->time)
    {
        Add_LastLG(caux, end);
        if (*waiting == NULL)
            break;
        end = Extract(waiting);
    }
    /* prioritate si timp egale, ID mai mic */
    while (end->priority == task->priority && end->time == task->time && end->ID < task->ID)
    {
        Add_LastLG(caux, end);
        if (*waiting == NULL)
            break;
        end = Extract(waiting);
    }
    /* adaugam task-ul necesar */
    Add_LastLG(caux, task);
    /* adaugam ce a ramas din coada initiala */
    if(*waiting != NULL || end->priority < task->priority)
        Add_LastLG(caux, end);
    while (*waiting != NULL)
    {
        end = Extract(waiting);
        Add_LastLG(caux, end);
    }

    /*-------Pas 2-------*/
    /* trebuie sa inversam caux in waiting */
    while (*caux != NULL)
    {
        end = Extract(caux);
        Add_LastLG(waiting, end);
    }
    free(caux);
    return 1;
}

int add_tasks(TLG *waiting, FILE *output, int n, unsigned long time,
              char priority, int *aparTask)
{
    int i = 0, j = 0;
    Task *task;
    for (i = 1; i <= n; i++)
    {
        /* atribuim ce cunoastem */
        task = malloc(sizeof(Task));
        task->time = time;
        task->priority = priority;

        /* cautam ID pentru task */
        for (j = 1; j <= MaxTask; j++)
        {
            if (aparTask[j] == 0) /* ID liber */
            {
                aparTask[j] = 1;
                task->ID = j;
                break;
            }
        }
        if (!add_waiting(waiting, task))
        {
            printf("Adaugare esuata\n");
            return 0;
        }
        else
            fprintf(output, "Task created successfully : ID %d.\n", task->ID);
    }
    return 1;
}

int get_task(TLG *coada, FILE *output, char *type, short ID)
{
    Task *task;
    TLG *caux = malloc(sizeof(TLG));
    *caux = NULL;
    int gasit = 0;
    while (*coada != NULL)
    {
        task = Extract(coada);
        if (!gasit && task->ID == ID)
        {
            fprintf(output, "Task %d is %s (remaining_time = %lu).\n",
                    ID, type, task->time);
            gasit = 1;
        }
        Add_LastLG(caux, task);
    }
    while (*caux != NULL)
    {
        task = Extract(caux);
        Add_LastLG(coada, task);
    }
    free(caux);
    return gasit;
}

int get_thread(TLG *stiva, char IDthread)
{
    Thread *thread;
    TLG *saux = malloc(sizeof(TLG));
    *saux = NULL;
    int gasit = 0;
    while (*stiva != NULL)
    {
        thread = Pop(stiva);
        if (thread->ID == IDthread)
            gasit = 1;
        Add_LastLG(saux, thread);
    }
    while (*saux != NULL)
    {
        thread = Pop(saux);
        Add_LastLG(stiva, thread);
    }
    free(saux);
    return gasit;
}

void print_thread(TLG *running, char IDthread, FILE *output)
{
    TLG *aux = malloc(sizeof(TLG));
    *aux = NULL;
    Task *task;
    while (*running != NULL)
    {
        task = Extract(running);
        if (task->thread.ID == IDthread)
            fprintf(output, "Thread %d is running task %hd (remaining_time = %lu).\n",
                    IDthread, task->ID, task->time);
        Add_LastLG(aux, task);
        if (*running)
            fprintf(output, ",\n");
    }
    while (*aux != NULL)
    {
        task = Extract(aux);
        Add_LastLG(running, task);
    }
}
