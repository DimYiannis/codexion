/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:11:20 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/08 10:13:57 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void init_queue(t_queue *queue, t_sim *sim)
{
  queue->coders = malloc(sizeof(t_coder *) * sim->args->num_of_coders);
  queue->size = 0;
}

void enqueue(t_queue *queue, t_coder *coder)
{
  queue->coders[queue->size] = coder;
  queue->size++;
}

t_coder *dequeue(t_queue *queue)
{
  t_coder *first;
  int i;

  i = 1;
  first = queue->coders[0];
  while (i < queue->size)
  {
    queue->coders[i - 1] = queue->coders[i];
    i++;
  }
  queue->size--;
  return (first);
}




