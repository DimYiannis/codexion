/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiannis <yiannis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:02:50 by ydimitra          #+#    #+#             */
/*   Updated: 2026/05/05 09:36:16 by yiannis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main(int argc, char *argv[])
{
   Myargs args;

    if (argc != 9)
        return (fprintf(stderr, "wrong number of arguments"), 1);
    parse_shit(argv, &args);
    return (0);
}
