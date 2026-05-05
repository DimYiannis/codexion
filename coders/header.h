/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiannis <yiannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:02:34 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/05 17:45:41 by yiannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>


typedef struct s_args
{
	int		num_of_coders;
	int		time_to_burnout;
	int		time_to_comp;
	int		time_to_debug;
	int		time_to_refactor;
	int		num_of_comps_required;
	int		dongle_cooldown;
	char	*scheduler;
}	Myargs;

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	mutex;
	int				can_use;
	int				cooldown;
}	t_dongle;

typedef struct s_coder
{
	int			id;
	int			time_to_burnout;
	t_dongle	*dongles;
	int			num_dongles;
}	t_coder;

typedef struct s_simulation
{
	Myargs		*args;
	t_coder		*coders;
	t_dongle	*dongles;
}	t_sim;



char	*ft_strcpy(char *dest, const char *src);
int		is_valid_arg(char *s);
void	parse_shit(char *argv[], Myargs *args);
void	check_shit(Myargs *args);
void	*threadFunc(void *arg);

#endif
