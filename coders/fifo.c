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

init_queue(t_sim *sim)
{
  t_queue queue;
  queue->coders = sim->coders;
  queue->size = sim->args->num_of_coders;
}

void dequeue(t_queue *queue, t_coder *coder)
{

}

t_coder *dequeue(t_queue *queue)
{

}




