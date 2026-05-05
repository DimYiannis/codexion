/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiannis <yiannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:22:41 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/05 09:24:24 by yiannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	parse_shit(char *argv[], Myargs *args)
{
	int	i;

	i = 1;
	while (i < 8)
	{
		if (!is_valid_arg(argv[i]))
		{
			fprintf(stderr, "invalid input '%s'\n", argv[i]);
			exit(1);
		}
		i++;
	}
	args->num_of_coders = atoi(argv[1]);
	args->time_to_burnout = atoi(argv[2]);
	args->time_to_comp = atoi(argv[3]);
	args->time_to_debug = atoi(argv[4]);
	args->time_to_refactor = atoi(argv[5]);
	args->num_of_comps_required = atoi(argv[6]);
	args->dongle_cooldown = atoi(argv[7]);
	args->scheduler = argv[8];
	check_shit(args);
}

void	check_shit(Myargs *args)
{
	if (args->num_of_coders < 1 || args->num_of_comps_required < 1)
	{
		fprintf(stderr, "invalid input, insert positive integers\n");
		exit(1);
	}
	if (strcmp(args->scheduler, "fifo") != 0 && strcmp(args->scheduler, "edf") != 0)
	{
		fprintf(stderr, "invalid input, value must be exactly one of: fifo or edf\n");
		exit(1);
	}
}
