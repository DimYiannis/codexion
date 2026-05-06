/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:06:34 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/06 10:06:51 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


pthread_mutex_t printlock;

void print_state(char *msg, int value)
{
  pthread_mutex_t_lock(&printlock);
  printf("%s: %d\n", msg, value);
  pthread_mutex_t_unlock(&printlock);
}
