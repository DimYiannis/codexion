/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:07:17 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/06 10:07:33 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void sched_init(t_dongle *dongle, t_sim *sim)
{
  if (strcmp(sim->args->scheduler, "fifo") == 0)
    init_queue(&dongle->queue, &sim);
  else
    init_heap(&dongle->queue, &sim);
}

void sched_add(t_dongle *dongle, t_coder *coder)
{
  if (strcmp(coder->sim->args->scheduler, "fifo") == 0)
    enqueue(&dongle->queue, &coder);
  else
    heap_push(&dongle->queue, &coder);
}

void sched_del(t_dongle *dongle, t_coder *coder)
{
  if (strcmp(coder->sim->args->scheduler, "fifo") == 0)
    dequeue(&dongle->queue);
  else
    heap_pop(&dongle->queue);
}
