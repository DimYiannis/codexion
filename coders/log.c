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

void print_state(t_coder *coder)
{
  pthread_mutex_t printlock;

  pthread_mutex_t_lock(&printlock);
  printf("%d: %d %s\n",time coder->id, message);
  pthread_mutex_t_unlock(&printlock);
}


void log_compiling(t_coder *coder)
{
  long ms;

  ms = get_time_ms(coder->sim->start_time);
  pthread_mutex_t_lock(&coder->sim->print_mutex);
  print("%ld %d is compiling\n");
  pthread_mutex_t_unlock(&coder->sim->print_mutex);
}

void log_debugging()
{
  long ms;

  ms = get_time_ms(coder->sim->start_time);
  pthread_mutex_t_lock(&coder->sim->print_mutex);
  print("%ld %d is compiling\n");
  pthread_mutex_t_unlock(&coder->sim->print_mutex);

}

void log_refactoring()
{
  long ms;

  ms = get_time_ms(coder->sim->start_time);
  pthread_mutex_t_lock(&coder->sim->print_mutex);
  print("%ld %d is compiling\n");
  pthread_mutex_t_unlock(&coder->sim->print_mutex);

}
void log_taken_dongle()
{
  long ms;

  ms = get_time_ms(coder->sim->start_time);
  pthread_mutex_t_lock(&coder->sim->print_mutex);
  print("%ld %d is compiling\n");
  pthread_mutex_t_unlock(&coder->sim->print_mutex);

}
void log_burnout()
{
  long ms;

  ms = get_time_ms(coder->sim->start_time);
  pthread_mutex_t_lock(&coder->sim->print_mutex);
  print("%ld %d is compiling\n");
  pthread_mutex_t_unlock(&coder->sim->print_mutex);

}

