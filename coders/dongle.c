
#include "header.h"

void	init_dongles(t_sim *sim)
{
	int	i;

	sim->dongles = malloc(sizeof(t_dongle) * sim->args->num_of_coders);
	i = 0;
	while (i < sim->args->num_of_coders)
	{
		sim->dongles[i].id = i;
		sim->dongles[i].can_use = 1;
		sim->dongles[i].cooldown = sim->args->dongle_cooldown;
		pthread_mutex_init(&sim->dongles[i].mutex, NULL);
		i++;
	}
}
