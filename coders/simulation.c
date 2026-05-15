/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:05:53 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/14 12:32:11 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
