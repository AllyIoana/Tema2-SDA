/* PATRASCU Ioana-Alexandra - grupa 314CB */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tlg.h"
#include "task.h"
#define MAX 15

int main(int argc, char *argv[])
{
    /* deschidere fisiere si citire date initiale*/
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    int Q, N, i = 0;
    char *cerinta = malloc(MAX * sizeof(char));
    unsigned long totalTime = 0;
    fscanf(input, "%d", &Q);
    fscanf(input, "%d", &N);
    N *= 2;

    /* definire stiva (pool) si cozi */
    TLG pool = NULL;
    TLG *waiting = malloc(sizeof(TLG));
    *waiting = NULL;
    TLG *running = malloc(sizeof(TLG));
    *running = NULL;
    TLG *finished = malloc(sizeof(TLG));
    *finished = NULL;
    /* initializare stiva */
    Thread elem;
    for (i = N - 1; i >= 0; i--)
    {
        elem.ID = (char)i;
        Add_LastLG(&pool, &elem);
    }

    /* pentru a gasi cele mai mici ID-uri: vectori de aparitie */
    int *aparTask = malloc(MaxTask * sizeof(int));
    memset(aparTask, 0, MaxTask * sizeof(int));

    /* impartirea cerintelor de rezolvat */
    while (fscanf(input, "%s", cerinta) > 0)
    {
        /*-------A-------*/
        if (strcmp("add_tasks", cerinta) == 0)
        {
            int number;
            fscanf(input, "%d", &number);
            unsigned long time;
            fscanf(input, "%lu", &time);
            char priority;
            fscanf(input, "%hhd", &priority);
            if (!add_tasks(waiting, output, number, time, priority, aparTask))
            {
                printf("eroare");
                return 0;
            }
        }

        /*-------B-------*/
        else if (strcmp("get_task", cerinta) == 0)
        {
            short ID;
            char *type = malloc(MAX * sizeof(char));
            fscanf(input, "%hd", &ID);
            strcpy(type, "waiting");
            if (!get_task(waiting, output, type, ID))
            {
                strcpy(type, "running");
                if (!get_task(running, output, type, ID))
                {
                    strcpy(type, "finished");
                    if (!get_task(finished, output, type, ID))
                        fprintf(output, "Task %d not found.\n", ID);
                }
            }
            free(type);
        }

        /*-------C-------*/
        else if (strcmp("get_thread", cerinta) == 0)
        {
            char thread;
            fscanf(input, "%hhd", &thread);
            if (thread <= (char)(N - 1))
            {
                if (!get_thread(&pool, thread))
                    fprintf(output, "Thread %d is idle.\n", thread);
                else
                    print_thread(running, thread, output);
            }
        }

        /*-------D, E, F-------*/
        else if (strcmp("print", cerinta) == 0)
        {
            fscanf(input, "%s", cerinta);

            /*-------PRINT WAITING-------*/
            if (strcmp("waiting", cerinta) == 0)
            {
                TLG *aux = malloc(sizeof(TLG));
                *aux = NULL;
                Task *end;
                fprintf(output, "====== Waiting queue =======\n[");
                while (*waiting != NULL)
                {
                    end = Extract(waiting);
                    fprintf(output, "(%d: priority = %hhd, remaining_time = %lu)",
                            end->ID, end->priority, end->time);
                    Add_LastLG(aux, end);
                    if (*waiting)
                        fprintf(output, ",\n");
                }
                while (*aux != NULL)
                {
                    end = Extract(aux);
                    Add_LastLG(waiting, end);
                }
                fprintf(output, "]\n");
                free(aux);
            }

            /*-------PRINT RUNNING-------*/
            else if (strcmp("running", cerinta) == 0)
            {
                TLG *aux = malloc(sizeof(TLG));
                *aux = NULL;
                Task *end;
                fprintf(output, "====== Running in parallel =======\n[");
                while (*running != NULL)
                {
                    end = Extract(running);
                    fprintf(output, "(%d: priority = %hhd, remaining_time = %lu, running_thread = %c)",
                            end->ID, end->priority, end->time, end->thread.ID);
                    Add_LastLG(aux, end);
                    if (*running)
                        fprintf(output, ",\n");
                }
                while (*aux != NULL)
                {
                    end = Extract(aux);
                    Add_LastLG(running, end);
                }
                fprintf(output, "]\n");
                free(aux);
            }

            /*-------PRINT FINISHED-------*/
            else
            {
                TLG *aux = malloc(sizeof(TLG));
                *aux = NULL;
                Task *end;
                fprintf(output, "====== Finished queue =======\n[");
                while (*finished != NULL)
                {
                    end = Extract(finished);
                    fprintf(output, "(%d: priority = %hhd, remaining_time = %lu, running_thread = %c)",
                            end->ID, end->priority, end->time, end->thread.ID);
                    Add_LastLG(aux, end);
                    if (*finished)
                        fprintf(output, ",\n");
                }
                while (*aux != NULL)
                {
                    end = Extract(aux);
                    Add_LastLG(finished, end);
                }
                fprintf(output, "]\n");
                free(aux);
            }
        }

        /*-------G-------*/
        else if (strcmp("run", cerinta) == 0)
        {
            unsigned long time;
            fscanf(input, "%lu", &time);
            fprintf(output, "Running tasks for %lu ms...\n", time);
            if(*running == NULL)
                run_waiting(waiting, running, &pool, time, &totalTime);
        }

        /*-------H-------*/
        else
        {
            fprintf(output, "Total time: %lu\n", totalTime);
        }
    }

    /* eliberare memorie */
    DistrugereStiva(&pool);
    DistrugereCoada(waiting);
    DistrugereCoada(running);
    DistrugereCoada(finished);
    fclose(input);
    fclose(output);
    free(cerinta);
    free(aparTask);
    return 0;
}
