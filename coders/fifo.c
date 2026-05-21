/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:11:20 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/13 11:21:17 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_queue(t_queue *queue, t_sim *sim)
{
	queue->coders = malloc(sizeof(t_coder *) * sim->args->num_of_coders);
	if (!queue->coders)
		return ;
	queue->size = 0;
}

void	enqueue(t_queue *queue, t_coder *coder)
{
	queue->coders[queue->size] = coder;
	queue->size++;
}

t_coder	*dequeue(t_queue *queue)
{
	t_coder	*first;
	int		i;

	if (queue->size == 0)
		return (NULL);
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

void	queue_remove(t_queue *queue, t_coder *coder)
{
	int	i;

	i = 0;
	while (i < queue->size && queue->coders[i] != coder)
		i++;
	if (i == queue->size)
		return ;
	while (i < queue->size - 1)
	{
		queue->coders[i] = queue->coders[i + 1];
		i++;
	}
	queue->size--;
}
