/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:06:10 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/06 10:06:23 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	check_burnout(t_sim *sim)
{
	int		i;
	long	now;

	i = 0;
	now = get_time_ms(sim->start);
	while (i < sim->args->num_of_coders)
	{
		if (now - sim->coders[i].last_compile > sim->args->time_to_burnout)
		{
			log_event(&sim->coders[i], "burned out");
			pthread_mutex_lock(&sim->stop_mutex);
			sim->stop = 1;
			pthread_mutex_unlock(&sim->stop_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_done(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args->num_of_coders)
	{
		if (sim->coders[i].compile_count < sim->args->num_of_comps_required)
			return (0);
		i++;
	}
	pthread_mutex_lock(&sim->stop_mutex);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (1);
}

static void	wake_dongles(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args->num_of_coders)
	{
		pthread_mutex_lock(&sim->dongles[i].mutex);
		pthread_cond_broadcast(&sim->dongles[i].cond);
		pthread_mutex_unlock(&sim->dongles[i].mutex);
		i++;
	}
}

void	*monitor(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	while (!sim->stop)
	{
		usleep(1000);
		if (check_burnout(sim))
			break ;
		if (check_done(sim))
			break ;
		wake_dongles(sim);
	}
	wake_dongles(sim);
	return (NULL);
}
