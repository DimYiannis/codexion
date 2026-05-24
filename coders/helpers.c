/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:07:38 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/13 13:04:34 by ydimitra         ###   ########.fr       */
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

    while (*s == '0' && i > 1)
    {
        s++;
        i--;
    }
	if (i > 10)
		return (0);
	if (i == 10 && strcmp(s, "2147483647") > 0)
		return (0);
	return (1);
}

long	get_time_ms(struct timeval start)
{
	long			result;
	long			sec;
	long			micro_sec;
	struct timeval	now;

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
	return (result);
}

void	swap(t_coder **a, t_coder **b)
{
	t_coder	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	min_deadln(t_coder *a, t_coder *b)
{
	if (a->deadline != b->deadline)
		return (a->deadline < b->deadline);
	return (a->id < b->id);
}

int	get_stop(t_sim *sim)
{
	int	stop;

	pthread_mutex_lock(&sim->print_mutex);
	stop = sim->stop;
	pthread_mutex_unlock(&sim->print_mutex);
	return (stop);
}
