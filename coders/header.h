/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiannis <yiannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:02:34 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/05 21:16:55 by yiannis          ###   ########.fr       */
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

typedef struct s_simulation t_sim;
typedef struct s_coder t_coder;

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
	pthread_cond_t	cond;
}	t_dongle;

typedef struct s_coder
{
	int			id;
	int			time_to_burnout;
	pthread_cond_t wait_cond;
	t_sim	*sim;
	int	compile_count;
	int last_compile;
	pthread_t thread;
}	t_coder;

typedef struct s_simulation
{
	Myargs		*args;
	t_coder		*coders;
	t_dongle	*dongles;
	pthread_t	*threads;
	int stop;
	int start;
	pthread_mutex_t stop_mutex;
	pthread_mutex_t print_mutex;
}	t_sim;



char	*ft_strcpy(char *dest, const char *src);
int		is_valid_arg(char *s);
void	parse_shit(char *argv[], Myargs *args);
void	check_shit(Myargs *args);
// void	*threadFunc(void *arg);
void	init_dongles(t_sim *sim);
void simulation(Myargs *args);


#endif
