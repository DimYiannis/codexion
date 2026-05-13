/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:05:53 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/13 11:27:38 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_sim(t_sim *sim, t_args *args)
{
	sim->args = args;
	sim->stop = 0;
	gettimeofday(&sim->start, NULL);
	pthread_mutex_init(&sim->stop_mutex, NULL);
	pthread_mutex_init(&sim->print_mutex, NULL);
	sim->coders = malloc(sizeof(t_coder) * args->num_of_coders);
	init_dongles(sim);
}

void	init_coders(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args->num_of_coders)
	{
		sim->coders[i].id = i + 1;
		sim->coders[i].time_to_burnout = sim->args->time_to_burnout;
		sim->coders[i].compile_count = 0;
		sim->coders[i].last_compile = 0;
		sim->coders[i].sim = sim;
		sim->coders[i].left_dongle = &sim->dongles[i];
		sim->coders[i].right_dongle = &sim->dongles[(i + 1)
			% sim->args->num_of_coders];
		pthread_mutex_init(&sim->coders[i].state_mutex, NULL);
		pthread_create(&sim->coders[i].thread, NULL, &routine,
			(void *)&sim->coders[i]);
		i++;
	}
}

void	simulation(t_args *args)
{
	int			i;
	t_sim		sim;
	pthread_t	monitor_thread;

	init_sim(&sim, args);
	init_coders(&sim);
	pthread_create(&monitor_thread, NULL, &monitor, &sim);
	i = 0;
	while (i < args->num_of_coders)
		pthread_join(sim.coders[i++].thread, NULL);
	pthread_join(monitor_thread, NULL);
	pthread_mutex_destroy(&sim.stop_mutex);
	pthread_mutex_destroy(&sim.print_mutex);
	i = 0;
	while (i < args->num_of_coders)
	{
		pthread_mutex_destroy(&sim.coders[i].state_mutex);
		free(sim.dongles[i].queue.coders);
		i++;
	}
	free(sim.coders);
	cleanup_dongles(&sim);
	free(sim.dongles);
}

void	cleanup_dongles(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args->num_of_coders)
	{
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		pthread_cond_destroy(&sim->dongles[i].cond);
		i++;
	}
}
