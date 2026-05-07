/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:05:24 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/06 10:05:29 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void *routine(void *arg)
{
  t_coder *coder;

  coder = arg;
  while(!coder->sim->stop)
  {
    acquire_dongles(coder);
    if(coder->sim->stop)
      break;
    coder->last_compile = get_time_ms(coder->sim->start);
    log_event(coder, "is compiling");
    usleep(coder->sim->args->time_to_comp * 1000);
    release_dongles(coder);
    coder->compile_count++;
    log_event(coder, "is debugging");
    usleep(coder->sim->args->time_to_debug * 1000);
    log_event(coder, "is refactoring");
    usleep(coder->sim->args->time_to_refactor * 1000);
  }
}
