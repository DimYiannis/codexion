
#include "header.h"

void simulation(Myargs *args)
{
    int i;
    int id;
    pthread_t *threads;
    t_coder *coders;

    threads = malloc(sizeof(pthread_t) * args->num_of_coders);
    coders = malloc(sizeof(t_coder) * args->num_of_coders);
    i = 0;
    while (i < args->num_of_coders)
    {
        coders[i].id = i + 1;
        coders[i].time_to_burnout = args->time_to_burnout;
        pthread_create(&threads[i], NULL, &threadFunc, (void*)&coders[i]);
        i++;
    }
    i = 0;
    while (i < args->num_of_coders)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    free(threads);
    free(coders);
}