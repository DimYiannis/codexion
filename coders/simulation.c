
#include "header.h"

void simulation(Myargs *args)
{
    int i;
    t_sim sim;
    pthread_t *threads;

    sim.args = args;
    threads = malloc(sizeof(pthread_t) * args->num_of_coders);
    sim.coders = malloc(sizeof(t_coder) * args->num_of_coders);
    init_dongles(&sim);
    i = 0;
    while (i < args->num_of_coders)
    {
        sim.coders[i].id = i + 1;
        sim.coders[i].time_to_burnout = args->time_to_burnout;
        sim.coders[i].dongles = sim.dongles;
        pthread_create(&threads[i], NULL, &threadFunc, (void*)&sim.coders[i]);
        i++;
    }
    i = 0;
    while (i < args->num_of_coders)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    free(threads);
    free(sim.coders);
    free(sim.dongles);
}