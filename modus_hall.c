/*
 * Authors: Anderson Henrique Giacomini - 769720
 * Gustavo Vieira Jodar - 769678
 * Lucas Cruz dos Reis(L.C.R.) - 754757
 * Sophia S Schuster - 760936
 * Tiago Lucas Leal - 760937
 * Desc.: A program to solve The Modus Hall Problem for the subject of
 * Operational Systems(SO) during the second semester of 2020.
 * I: <entry>
 * O: <output>
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

int heathens_counter = 0;
int prudes_counter = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t heathens_turn;
sem_t prudes_turn;

void
prudes(void)
{
    pthread_mutex_lock(&mutex);

    prudes_counter++;
    printf("\n%sPRUDES ARRIVED%s\nPrudes: %d\nHeathens: %d",
            "\033[31;1m", "\033[00m",
            prudes_counter, heathens_counter);
    pthread_mutex_unlock(&mutex);

    sem_wait(&prudes_turn);
    pthread_mutex_lock(&mutex);
    prudes_counter--;

    if (!prudes_counter && heathens_counter)
        sem_post(&heathens_turn);

    if (heathens_counter > prudes_counter)
        sem_post(&heathens_turn);
    else
        sem_post(&prudes_turn);

    printf("\n%sPRUDES FINISHED%s\nPrudes: %d\nHeathens: %d",
            "\033[31;1m", "\033[00m",
            prudes_counter, heathens_counter);

    pthread_mutex_unlock(&mutex);
}

void
heathens(void)
{
    pthread_mutex_lock(&mutex);

    heathens_counter++;
    printf("\n%sHEATHENS ARRIVED%s\nPrudes: %d\nHeathens: %d",
            "\033[31;1m", "\033[00m",
            prudes_counter, heathens_counter);
    pthread_mutex_unlock(&mutex);

    sem_wait(&heathens_turn);

    pthread_mutex_lock(&mutex);
    heathens_counter--;

    if (!heathens_counter && prudes_counter)
        sem_post(&prudes_turn);

    if (prudes_counter > heathens_counter)
        sem_post(&prudes_turn);
    else
        sem_post(&heathens_turn);

    printf("\n%sHEATHENS FINISHED%s\nPrudes: %d\nHeathens: %d",
            "\033[31;1m", "\033[00m",
            prudes_counter, heathens_counter);

    pthread_mutex_unlock(&mutex);
}

void
run()
{
    int i;
    int num_heathens, num_prudes, start;
    pthread_t *tid_prudes, *tid_heathens;


    num_heathens = 20;
    num_prudes = 20;

    if (num_heathens > num_prudes)
        start = 1;
    else
        start = 0;

    tid_heathens = malloc(num_heathens * sizeof(pthread_t));
    tid_prudes = malloc(num_prudes * sizeof(pthread_t));

    if (sem_init(&heathens_turn, 0, start) < 0) 
        exit(1);

    if (sem_init(&prudes_turn, 0, !start) < 0) 
        exit(1);

    if (num_heathens >= num_prudes) {
        for (i = 0; i < num_prudes; i++) {
            pthread_create(&tid_prudes[i], NULL, &heathens, NULL);
            if (i < num_prudes)
                pthread_create(&tid_prudes[i], NULL, &prudes, NULL);
        }


        for (i = 0; i < num_heathens; i++) {
            pthread_join(tid_heathens[i], NULL);
            if (i < num_prudes)
                pthread_join(tid_prudes[i], NULL);
        }
    } else {
        for(i = 0; i < num_prudes; i++) {
            pthread_create(&tid_prudes[i], NULL, &prudes, NULL);
            if (i < num_heathens)
                pthread_create(&tid_heathens[i], NULL, &heathens, NULL);
        }

        for (i = 0; i < num_prudes; i++) {
            pthread_join(tid_prudes[i], NULL);
            if (i < num_heathens)
                pthread_join(tid_heathens[i], NULL);
        }
    }
}

int
main(int argc, char *argv[])
{
    run();

    return 0;
}
