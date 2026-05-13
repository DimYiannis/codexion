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

typedef struct s_simulation	t_sim;
typedef struct s_coder		t_coder;

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

typedef struct s_queue
{
	t_coder **coders;  // array of pointer to access the originals
	int size;
} t_queue;

typedef struct s_dongle
{
	int				id;
	int				in_use;
	long			free_at;
	int				cooldown;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_queue			queue;
}	t_dongle;

typedef struct s_coder
{
	int id;
	int time_to_burnout;
	t_sim *sim;
	int compile_count;
	long last_compile;
	pthread_t thread;
  t_dongle *left_dongle;
	t_dongle *right_dongle;
  pthread_mutex_t state_mutex;
}	t_coder;

typedef struct s_simulation
{
	Myargs *args;
	t_coder *coders;
	t_dongle *dongles;
	pthread_t *threads;
	int stop;
	struct timeval  start;
	pthread_mutex_t stop_mutex;
	pthread_mutex_t print_mutex;
}	t_sim;

// parser
void	parse_shit(char *argv[], Myargs *args);
void	check_shit(Myargs *args);

void simulation(Myargs *args);
void log_event(t_coder *coder, char *msg);
void *routine(void *arg);
void	*monitor(void *arg);
void	cleanup_dongles(t_sim *sim);

// fifo.c
void init_queue(t_queue *queue, t_sim *sim);
void enqueue(t_queue *queue, t_coder *coder);
t_coder *dequeue(t_queue *queue);

// edf.c
void init_heap(t_queue *queue, t_sim *sim);
void heap_push(t_queue *queue, t_coder *coder);
t_coder *heap_pop(t_queue *queue);

// helpers.c
void swap(t_coder **a, t_coder **b);
long get_deadline(t_coder *coder);
long get_time_ms(struct timeval start);
int is_valid_arg(char *s);

// scheduler.c
void sched_init(t_dongle *dongle, t_sim *sim);
void sched_add(t_dongle *dongle, t_coder *coder);
void sched_del(t_dongle *dongle, t_coder *coder);

//dongles.c
void  acquire_dongles(t_coder *coder);
void  init_dongles(t_sim *sim);
void release_dongles(t_coder *coder);

#endif
