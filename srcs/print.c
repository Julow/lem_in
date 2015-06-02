/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 01:21:10 by juloo             #+#    #+#             */
/*   Updated: 2015/06/03 01:06:18 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

STATIC void		print_rooms(t_lem *lem, int flag)
{
	int				i;

	i = -1;
	while (++i < lem->room_count)
		if (lem->rooms[i].flags == flag)
			P("(%d) %s %d %d\n", i, lem->rooms[i].name,
				lem->rooms[i].x, lem->rooms[i].y);
}

STATIC void		print_links(t_lem *lem)
{
	int				i;
	int				j;

	i = -1;
	while (++i < lem->room_count)
	{
		j = -1;
		while (++j < i)
			if (lem->links[i][j])
				P("%s-%s\n", lem->rooms[i].name, lem->rooms[j].name);
	}
}

void			print_lem(t_lem *lem)
{
	PI(lem->ant_count);
	PS("\n##start\n");
	print_rooms(lem, ROOM_START);
	PS("##end\n");
	print_rooms(lem, ROOM_END);
	print_rooms(lem, 0);
	print_links(lem);
	NL;
}
