/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:28:37 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/14 12:33:02 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_sim(t_sim *sim, t_args *args)
{
	sim->args = args;
	sim->stop = 0;
	gettimeofday(&sim->start, NULL);
	pthread_mutex_init(&sim->print_mutex, NULL);
	sim->coders = malloc(sizeof(t_coder) * args->num_of_coders);
	if (!sim->coders)
	{
		fprintf(stderr, "malloc failed\n");
		exit(1);
	}
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

void	init_dongles(t_sim *sim)
{
	int	i;

	sim->dongles = malloc(sizeof(t_dongle) * sim->args->num_of_coders);
	if (!sim->dongles)
	{
		fprintf(stderr, "malloc failed\n");
		exit(1);
	}
	i = 0;
	while (i < sim->args->num_of_coders)
	{
		sim->dongles[i].id = i;
		sim->dongles[i].in_use = 0;
		sim->dongles[i].free_at = 0;
		sim->dongles[i].cooldown = sim->args->dongle_cooldown;
		pthread_mutex_init(&sim->dongles[i].mutex, NULL);
		pthread_cond_init(&sim->dongles[i].cond, NULL);
		sched_init(&sim->dongles[i], sim);
		i++;
	}
}
