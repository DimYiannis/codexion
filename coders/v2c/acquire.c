/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acquire.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 10:00:00 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/15 10:00:00 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
** Wait until we are queue[0], dongle free, cooldown elapsed.
** Sets in_use=1 on success. Does NOT dequeue — coder stays at queue[0].
** Returns 0 if stop was set before conditions met.
*/
static int	wait_and_take(t_coder *coder, t_dongle *first)
{
	pthread_mutex_lock(&first->mutex);
	while (!get_stop(coder->sim) && (first->in_use
			|| get_time_ms(coder->sim->start) < first->free_at
			|| first->queue.coders[0] != coder))
		pthread_cond_wait(&first->cond, &first->mutex);
	if (get_stop(coder->sim))
	{
		pthread_mutex_unlock(&first->mutex);
		return (0);
	}
	first->in_use = 1;
	pthread_mutex_unlock(&first->mutex);
	return (1);
}

/*
** Non-blocking attempt on second dongle.
** No queue interaction — only takes if queue empty + free + cooldown ok.
*/
static int	try_second(t_coder *coder, t_dongle *second)
{
	int	ok;

	pthread_mutex_lock(&second->mutex);
	ok = !second->in_use && second->queue.size == 0
		&& get_time_ms(coder->sim->start) >= second->free_at
		&& !get_stop(coder->sim);
	if (ok)
		second->in_use = 1;
	pthread_mutex_unlock(&second->mutex);
	return (ok);
}

/*
** Release hold on first dongle (set in_use=0) WITHOUT dequeuing.
** Coder stays at queue[0] for the next retry.
*/
static void	release_hold(t_coder *coder, t_dongle *first)
{
	pthread_mutex_lock(&first->mutex);
	first->in_use = 0;
	first->free_at = get_time_ms(coder->sim->start);
	pthread_cond_broadcast(&first->cond);
	pthread_mutex_unlock(&first->mutex);
}

/*
** Dequeue coder from first dongle queue and wake next waiter.
** Called only when both dongles acquired, or on stop cleanup.
*/
static void	pop_and_wake(t_coder *coder, t_dongle *first)
{
	pthread_mutex_lock(&first->mutex);
	if (first->queue.size > 0 && first->queue.coders[0] == coder)
		sched_del(first, coder);
	pthread_cond_broadcast(&first->cond);
	pthread_mutex_unlock(&first->mutex);
}

/*
** Enqueue on first dongle (with deadline snapshot), wait until both
** dongles acquired. Dequeues from first ONLY on success or stop cleanup.
** Returns 1 if both acquired, 0 if stopped.
*/
int	acquire_pair(t_coder *coder, t_dongle *first, t_dongle *second)
{
	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&coder->state_mutex);
	coder->deadline = coder->last_compile + coder->time_to_burnout;
	pthread_mutex_unlock(&coder->state_mutex);
	sched_add(first, coder);
	pthread_mutex_unlock(&first->mutex);
	while (!get_stop(coder->sim))
	{
		if (!wait_and_take(coder, first))
			break ;
		if (try_second(coder, second))
		{
			pop_and_wake(coder, first);
			return (1);
		}
		release_hold(coder, first);
		usleep(2000);
	}
	pop_and_wake(coder, first);
	return (0);
}
