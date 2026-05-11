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

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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
  result = (now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec - start.tv_usec) / 1000;
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
