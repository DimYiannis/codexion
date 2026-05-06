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
		sim->dongles[i].can_use = 1;
		sim->dongles[i].cooldown = sim->args->dongle_cooldown;
		pthread_mutex_init(&sim->dongles[i].mutex, NULL);
    pthread_cond_init(&sim->dongles[i].cond, NULL);
		i++;
	}
}
