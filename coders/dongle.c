/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:05:33 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/06 10:05:37 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_dongles(t_sim *sim)
{
	int	i;

	sim->dongles = malloc(sizeof(t_dongle) * sim->args->num_of_coders);
	i = 0;
	while (i < sim->args->num_of_coders)
	{
		sim->dongles[i].id = i;
		sim->dongles[i].in_use = 0;
    sim->dongle[i].free_at = 0;
		sim->dongles[i].cooldown = sim->args->dongle_cooldown;
		pthread_mutex_init(&sim->dongles[i].mutex, NULL);
    pthread_cond_init(&sim->dongles[i].cond, NULL);
    sched_init(&sim->dongles[i], sim);
		i++;
	}
}


void acquire_dongles(t_coder *coder)
{
  int n;

  n = coder->sim->args->num_of_coders;
  if (n == 1)
  {
    acquire_one(coder, coder->left_dongle);
    return;
  }
  if (coder->id == n)
  {
    acquire_one(coder, coder->left_dongle);
    acquire_one(coder, coder->right_dongle);
  }
  else
  {
    acquire_one(coder, coder->left_dongle);
    acquire_one(coder, coder->right_dongle);
  }
}

void release_dongles(t_coder *coder)
{
  int n;

  n = coder->sim->args->num_of_coders;
  if (n == 1)
  {
    release_one(coder, coder->left_dongle);
    return;
  }
  release_one(coder, coder->left_dongle);
  release_one(coder, coder->right_dongle);
}

static void acquire_one(t_coder *coder, t_dongle *dongle)
{
  pthread_mutex_lock(&dongle->mutex);
  sched_add(dongle, coder);
  while (!coder->sim->stop)
  {
    if (!dongle->in_use && get_time_ms(coder->sim->start) >= dongle->free_at && dongle->queue.coders[0] == coder)
      break;
    pthread_cond_wait(&dongle->cond, &dongle->mutex);
  }
  if (coder->sim->stop)
  {
    pthread_mutex_unlock(&dongle->mutex)
    return;
  }
  sched_del(dongle, coder);
  dongle->in_use = 1;
  pthread_mutex_unlock(&dongle->mutex);
  log_event(coder, "has taken a dongle");
}

static void release_one(t_coder *coder, t_dongle *dongle)
{
  pthread_mutex_lock(&dongle->mutex);
  dongle->in_use = 0;
  dongle->free_at = get_time_ms(coder->sim->start) + dongle->cooldown;
  pthread_cond_broadcast(&dongle->cond);
  pthread_mutex_unlock(&dongle->mutex);
}
