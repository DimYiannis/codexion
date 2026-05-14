/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:05:33 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/14 14:43:01 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	acquire_one(t_coder *coder, t_dongle *dongle, int blocked);
static void	release_one(t_coder *coder, t_dongle *dongle, int blocked);

void	acquire_dongles(t_coder *coder)
{
	int			n;
	t_dongle	*first;
	t_dongle	*second;

	n = coder->sim->args->num_of_coders;
	if (n == 1)
		return (acquire_one(coder, coder->left_dongle, 1), log_event(coder,
				"has taken a dongle"));
	first = coder->left_dongle;
	second = coder->right_dongle;
	if (coder->id == n)
	{
		first = coder->right_dongle;
		second = coder->left_dongle;
	}
	while (!coder->sim->stop)
	{
		if (!acquire_one(coder, first, 1))
			return ;
		if (acquire_one(coder, second, 0))
			return (log_event(coder, "has taken a dongle"), usleep(1000), log_event(coder,
					"has taken a dongle"));
		release_one(coder, first, 1);
		usleep(1000);
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

static int	acquire_one(t_coder *coder, t_dongle *dongle, int blocked)
{
	pthread_mutex_lock(&dongle->mutex);
	sched_add(dongle, coder);
	while (!coder->sim->stop)
	{
		if (!dongle->in_use && get_time_ms(coder->sim->start) >= dongle->free_at
			&& dongle->queue.coders[0] == coder)
			break ;
		if (!blocked)
			break ;
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
	if (!coder->sim->stop && !dongle->in_use
		&& get_time_ms(coder->sim->start) >= dongle->free_at
		&& dongle->queue.coders[0] == coder)
	{
		sched_del(dongle, coder);
		dongle->in_use = 1;
		pthread_mutex_unlock(&dongle->mutex);
		return (1);
	}
	sched_del(dongle, coder);
	pthread_mutex_unlock(&dongle->mutex);
	return (0);
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
