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

void init_sim(t_sim *sim, Myargs *args)
{
  sim->args = args;
  sim->stop = 0;
  gettimeofday(&sim->start, NULL);
  pthread_mutex_init(&sim->stop_mutex, NULL);
  pthread_mutex_init(&sim->print_mutex,NULL);
  sim->coders = malloc(sizeof(t_coder) * args->num_of_coders);
  init_dongles(sim);
}

void init_coders(t_sim *sim)
{
  int i;

  i = 0;
  while (i < sim->args->num_of_coders)
  {
    sim->coders[i].id = i + 1;
    sim->coders[i].time_to_burnout = sim->args->time_to_burnout;
    sim->coders[i].compile_count = 0;
    sim->coders[i].last_compile = 0 ;
    sim->coders[i].sim = sim; //back pointer for access to args
    pthread_create(&sim->coders[i].thread, NULL, &routine, (void*)&sim->coders[i]);
    i++;
  }
}

void simulation(Myargs *args)
{
  int i;
  t_sim sim;

  init_sim(&sim, args);
  init_coders(&sim);
  i = 0;
  while (i < args->num_of_coders)
  {
    pthread_join(sim.coders[i].thread, NULL);
    i++;
  }
  pthread_mutex_destroy(&sim.stop_mutex);
  pthread_mutex_destroy(&sim.print_mutex);
  free(sim.coders);
  free(sim.dongles);
}
