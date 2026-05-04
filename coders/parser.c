/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:22:41 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/04 11:22:42 by ydimitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "header.h"

void parse_shit(char *argv[], struct Myargs *args)
{
  args->num_of_coders = atoi(argv[1]);
  args->time_to_burnout = atoi(argv[2]);
  args->time_to_comp = atoi(argv[3]);
  args->time_to_debug = atoi(argv[4]);
  args->time_to_refactor = atoi(argv[5]);
  args->num_of_comps_required = atoi(argv[6]);
  args->dongle_cooldown = atoi(argv[7]);
  args->scheduler = argv[8];
}
