/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:05:24 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/14 15:11:32 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*routine(void *arg)
{
	t_coder	*coder;

	coder = arg;
	while (!get_stop(coder->sim))
	{
		acquire_dongles(coder);
		if (get_stop(coder->sim) || coder->sim->args->num_of_coders == 1)
			break ;
		pthread_mutex_lock(&coder->state_mutex);
		coder->last_compile = get_time_ms(coder->sim->start);
		pthread_mutex_unlock(&coder->state_mutex);
		log_event(coder, "is compiling");
		usleep(coder->sim->args->time_to_comp * 1000);
		release_dongles(coder);
		pthread_mutex_lock(&coder->state_mutex);
		coder->compile_count++;
		pthread_mutex_unlock(&coder->state_mutex);
		log_event(coder, "is debugging");
		usleep(coder->sim->args->time_to_debug * 1000);
		log_event(coder, "is refactoring");
		usleep(coder->sim->args->time_to_refactor * 1000);
	}
	return (NULL);
}
