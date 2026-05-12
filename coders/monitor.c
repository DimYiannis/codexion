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


static int check_burnout(t_sim *sim)
{
  int i;

  i = 0;
  while (i < sim->args->num_of_coders)
  {

  }
}

release_one becomes dead simple:                                           
  pthread_mutex_lock(&d->mutex);
  d->in_use = 0;                                                             
  d->free_at = get_time_ms(coder->sim->start) + d->cooldown;
  pthread_cond_broadcast(&d->cond);                         
  pthread_mutex_unlock(&d->mutex); 
