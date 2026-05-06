/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:05:53 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/06 10:05:57 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void simulation(Myargs *args)
{
    int i;
    t_sim sim;
    sim.args = args;

    sim.coders = malloc(sizeof(t_coder) * args->num_of_coders);
    init_dongles(&sim);
    i = 0;
    while (i < args->num_of_coders)
    {
        sim.coders[i].id = i + 1;
        sim.coders[i].time_to_burnout = args->time_to_burnout;
        sim.coders[i].sim = &sim; //back pointer
        pthread_create(&sim.coders[i].thread, NULL, &threadFunc, (void*)&sim.coders[i]);
        i++;
    }
    i = 0;
    while (i < args->num_of_coders)
    {
        pthread_join(sim.coders[i].thread, NULL);
        i++;
    }
    free(sim.coders);
    free(sim.dongles);
}
