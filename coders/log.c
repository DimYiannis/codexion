/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:06:34 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/13 11:22:07 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	log_event(t_coder *coder, char *msg)
{
	long	ms;

	ms = get_time_ms(coder->sim->start);
	pthread_mutex_lock(&coder->sim->print_mutex);
	printf("%ld %d %s\n", ms, coder->id, msg);
	pthread_mutex_unlock(&coder->sim->print_mutex);
}
