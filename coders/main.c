# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    main.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydimitra <ydimitra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/04 11:02:50 by ydimitra          #+#    #+#              #
#    Updated: 2026/05/04 11:05:52 by ydimitra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#include "header.h"

int main(int argc, char *argv[])
{
   struct Myargs args;

    if (argc != 8)
        return (1);
    else:
        parse_shit(argv, &args);

}
