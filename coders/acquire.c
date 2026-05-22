/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 12:09:57 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/15 12:10:08 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	wait_and_take(t_coder *coder, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	while (!get_stop(coder->sim))
	{
		if (!d->in_use
			&& get_time_ms(coder->sim->start) >= d->free_at
			&& d->queue.size > 0
			&& d->queue.coders[0] == coder)
			break ;
		pthread_cond_wait(&d->cond, &d->mutex);
	}
	if (get_stop(coder->sim))
	{
		pthread_mutex_unlock(&d->mutex);
		return (0);
	}
	d->in_use = 1;
	pthread_mutex_unlock(&d->mutex);
	return (1);
}

static void	pop_and_wake(t_coder *coder, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	if (d->queue.size > 0 && d->queue.coders[0] == coder)
		sched_del(d, coder);
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->mutex);
}

static void	release_silent(t_coder *coder, t_dongle *first, t_dongle *second)
{
	pthread_mutex_lock(&second->mutex);
	sched_remove(second, coder);
	pthread_cond_broadcast(&second->cond);
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_lock(&first->mutex);
	first->in_use = 0;
	first->free_at = get_time_ms(coder->sim->start);
	pthread_cond_broadcast(&first->cond);
	pthread_mutex_unlock(&first->mutex);
}

static int	enqueue_and_wait(t_coder *coder, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	sched_add(d, coder);
	pthread_mutex_unlock(&d->mutex);
	if (!wait_and_take(coder, d))
	{
		pop_and_wake(coder, d);
		return (0);
	}
	pop_and_wake(coder, d);
	return (1);
}

int	acquire_pair(t_coder *coder, t_dongle *first, t_dongle *second)
{
	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&coder->state_mutex);
	coder->deadline = coder->last_compile + coder->time_to_burnout;
	pthread_mutex_unlock(&coder->state_mutex);
	sched_add(first, coder);
	pthread_mutex_unlock(&first->mutex);
	if (!wait_and_take(coder, first))
	{
		pop_and_wake(coder, first);
		return (0);
	}
	pop_and_wake(coder, first);
	if (!enqueue_and_wait(coder, second))
	{
		release_silent(coder, first, second);
		return (0);
	}
	return (1);
}
