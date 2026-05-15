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


static int wait_and_take(t_coder *coder, t_dongle *first)
{
  pthread_mutex_lock(&first->mutex);
  while (!get_stop(coder->sim) && (first->in_use || get_time_ms(coder->sim->start) < first->free_at || return_first(&first->queue) != coder))
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

static int try_second(t_coder *coder, t_dongle *second)
{
  int ok;

  pthread_mutex_lock(&second->mutex);
  ok = !second->in_use
    && get_time_ms(coder->sim->start) >= second->free_at
    && !get_stop(coder->sim);
  if (ok)
    second->in_use = 1;
  pthread_mutex_unlock(&second->mutex);
  return (ok);
}

static void release_hold(t_coder *coder, t_dongle *first)
{
  pthread_mutex_lock(&first->mutex);
  first->in_use = 0;
  first->free_at = get_time_ms(coder->sim->start);
  pthread_cond_broadcast(&first->cond);
  pthread_mutex_unlock(&first->mutex);
}

static void pop_and_wake(t_coder *coder, t_dongle *first)
{
  pthread_mutex_lock(&first->mutex);
  if(first->queue.size > 0 && first->queue.coders[0] == coder)
    sched_del(first, coder);
  pthread_cond_broadcast(&first->cond);
  pthread_mutex_unlock(&first->mutex);
}

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
