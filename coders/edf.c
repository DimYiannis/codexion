/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:11:23 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/08 10:13:51 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void init_heap(t_queue *queue, t_sim *sim)
{
  queue->coders = malloc(sizeof(t_coder *) * sim->args->num_of_coders);
  if (!queue->coders)
    return;
  queue->size = 0;
}

void heapify_down(t_queue *queue, int size, int i)
{

}


void heapify_up(t_coder **coders, int index)
{
  while (index > 0 && coders[(index - 1) / 2]):
  {
    swap(&coders[index], &coders[(index - 1) / 2]);
    index = (index - 1) / 2;
  }
}


void heap_push(t_queue *queue, t_sim *coder)
{
  int index;

  queue->coders[queue->size] = coder;
  index = queue->size;
  queue->size++;
  // heapify up
  heapify_up(queue->coders, index);
}

void heap_pop(t_queue *queue)
{
  int index;
  int i;

  index = -1;
  i = 0;
  while(i < queue->size)
  {
    if (queue->coders[i] == queue->coders[0])
    {
      index = i;
      break;
    }
  }
  //valuue not found
  if (index == -1)
    return;
  queue->coders[index] = queue->coders[index - 1];
  queue->size--;
  //heapify down
}


