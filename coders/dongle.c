/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:05:33 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/15 12:10:08 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	release_one(t_coder *coder, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	d->in_use = 0;
	d->free_at = get_time_ms(coder->sim->start) + d->cooldown;
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->mutex);
}

static void	acquire_solo(t_coder *coder, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	sched_add(d, coder);
	while (!get_stop(coder->sim))
	{
		if (!d->in_use && get_time_ms(coder->sim->start) >= d->free_at
			&& d->queue.size > 0 && d->queue.coders[0] == coder)
			break ;
		pthread_cond_wait(&d->cond, &d->mutex);
	}
	sched_del(d, coder);
	if (!get_stop(coder->sim))
		d->in_use = 1;
	pthread_mutex_unlock(&d->mutex);
	log_event(coder, "has taken a dongle");
}

void	acquire_dongles(t_coder *coder)
{
	int			n;
	t_dongle	*first;
	t_dongle	*second;

	n = coder->sim->args->num_of_coders;
	if (n == 1)
		return (acquire_solo(coder, coder->left_dongle));
	first = coder->left_dongle;
	second = coder->right_dongle;
	if (coder->id == n)
	{
		first = coder->right_dongle;
		second = coder->left_dongle;
	}
	if (!acquire_pair(coder, first, second))
		return ;
	log_event(coder, "has taken a dongle");
	log_event(coder, "has taken a dongle");
}

void	release_dongles(t_coder *coder)
{
	int	n;

	n = coder->sim->args->num_of_coders;
	if (n == 1)
	{
		release_one(coder, coder->left_dongle);
		return ;
	}
	release_one(coder, coder->right_dongle);
	release_one(coder, coder->left_dongle);
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
