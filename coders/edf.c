/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:11:23 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/13 13:05:48 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_heap(t_queue *queue, t_sim *sim)
{
	queue->coders = malloc(sizeof(t_coder *) * sim->args->num_of_coders);
	if (!queue->coders)
		return ;
	queue->size = 0;
}

void	heapify_down(t_queue *queue, int size, int i)
{
	int	left;
	int	right;
	int	root;

	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		root = i;
		if ((left < size) && min_deadln(queue->coders[left],
				queue->coders[root]))
			root = left;
		if (right < size && min_deadln(queue->coders[right],
				queue->coders[root]))
			root = right;
		if (root == i)
			break ;
		swap(&queue->coders[i], &queue->coders[root]);
		i = root;
	}
}

void	heapify_up(t_coder **coders, int index)
{
	int	parent;

	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (min_deadln(coders[index], coders[parent]))
		{
			swap(&coders[index], &coders[parent]);
			index = parent;
		}
		else
			break ;
	}
}

void	heap_push(t_queue *queue, t_coder *coder)
{
	int	index;

	queue->coders[queue->size] = coder;
	index = queue->size;
	queue->size++;
	heapify_up(queue->coders, index);
}

t_coder	*heap_pop(t_queue *queue)
{
	t_coder	*root;

	if (queue->size == 0)
		return (NULL);
	root = queue->coders[0];
	queue->coders[0] = queue->coders[queue->size - 1];
	queue->size--;
	heapify_down(queue, queue->size, 0);
	return (root);
}
