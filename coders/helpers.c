/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiannis <yiannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:07:38 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/05 09:23:40 by yiannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_valid_arg(char *s)
{
	int	i;

	if (!s || s[0] == '\0')
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long get_time_ms(struct timeval start)
{
  long result;
  long sec;
  long micro_sec;
  struct timeval now;

  result = 0;
  gettimeofday(&now, NULL);
  sec = now.tv_sec - start.tv_sec;
  micro_sec = now.tv_usec - start.tv_usec;
  if (micro_sec < 0)
  {
    sec -= 1;
    micro_sec += 1000000;
  }
  result = sec * 1000 + micro_sec / 1000;
  return result;
}

void swap(t_coder **a, t_coder **b)
{
  t_coder *temp;

  temp = *a;
  *a = *b;
  *b = temp;
}

long get_deadline(t_coder *coder)
{
	return (coder->last_compile + coder->time_to_burnout);
}
