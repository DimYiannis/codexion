/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:05:33 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/15 10:00:00 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	acquire_one(t_coder *coder, t_dongle *dongle);
static void	release_one(t_coder *coder, t_dongle *dongle, int blocked);

/*
** 1-coder edge case: only 1 dongle, no pair needed.
** Enqueue, wait, take, dequeue. Standard acquire with pop.
*/
static void	acquire_one(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	sched_add(dongle, coder);
	while (!get_stop(coder->sim) && (dongle->in_use
			|| get_time_ms(coder->sim->start) < dongle->free_at))
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	if (!get_stop(coder->sim))
	{
		sched_del(dongle, coder);
		dongle->in_use = 1;
	}
	else
		sched_del(dongle, coder);
	pthread_mutex_unlock(&dongle->mutex);
}

void	acquire_dongles(t_coder *coder)
{
	int			n;
	t_dongle	*first;
	t_dongle	*second;

	n = coder->sim->args->num_of_coders;
	if (n == 1)
		return (acquire_one(coder, coder->left_dongle), log_event(coder,
				"has taken a dongle"));
	first = coder->left_dongle;
	second = coder->right_dongle;
	if (coder->id == n)
	{
		first = coder->right_dongle;
		second = coder->left_dongle;
	}
	if (acquire_pair(coder, first, second))
	{
		log_event(coder, "has taken a dongle");
		log_event(coder, "has taken a dongle");
	}
}

void	release_dongles(t_coder *coder)
{
	int	n;

	n = coder->sim->args->num_of_coders;
	if (n == 1)
	{
		release_one(coder, coder->left_dongle, 0);
		return ;
	}
	release_one(coder, coder->left_dongle, 0);
	release_one(coder, coder->right_dongle, 0);
}

static void	release_one(t_coder *coder, t_dongle *dongle, int blocked)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->in_use = 0;
	if (blocked == 0)
		dongle->free_at = get_time_ms(coder->sim->start) + dongle->cooldown;
	else
		dongle->free_at = get_time_ms(coder->sim->start);
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
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
