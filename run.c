/* PATRASCU Ioana-Alexandra - grupa 314CB */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tlg.h"
#include "task.h"

void run_waiting(TLG *waiting, TLG *running, TLG *pool,
                 unsigned long time, unsigned long *totalTime)
{
    /* din coada waiting sunt mutate in coada running */
    Thread *thread;
    Task *task;
    /* cautam thread-uri libere pentru a muta task-urile */
    while (*pool != NULL)
    {
        thread = Pop(pool);
        task = Extract(waiting);
        task->thread.ID = thread->ID;
        Add_LastLG(running, task);
        (*totalTime) += task->time;
    }
}

// void run_finished(TLG *waiting, TLG *running, TLG *finished,
//                   unsigned long time, unsigned long *totalTime)
// {
//     /* din coada de running sunt mutate in coada finished si se elibereaza thread */
//     Thread *thread;
//     Task *task;
//     TLG *raux = malloc(sizeof(TLG));
//     raux = NULL;
//     while (*running != NULL)
//     {
//         task = Extract(running);
//         if (task->time - time < 0)
//         {
//             Add_LastLG(finished, task);


//         }
//         else
//         {
//             task->time -= time;
//             Add_LastLG(raux, task);
//         }
       
//     }

//     while (*raux != NULL)
//     {
//         task = Extract(raux);
//         Add_LastLG(running, task);
//     }

//     free(raux);
// }