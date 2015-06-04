/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 12:50:55 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/04 15:01:24 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

STATIC void		move_path(t_lem *lem, t_path path)
{
	int				i;

	i = path.length - 1;
	while (--i > 0)
		if (path.rooms[i]->ant != 0)
		{
			if (path.rooms[i + 1]->flags & ROOM_END)
				lem->end_room->ant++;
			else if (path.rooms[i + 1]->ant != 0)
				PS(" CONFLICT:");
			else
				path.rooms[i + 1]->ant = path.rooms[i]->ant;
			P(" L%d-%s", path.rooms[i]->ant, path.rooms[i + 1]->name);
			path.rooms[i]->ant = 0;
		}
}

STATIC void		move_lem(t_lem *lem)
{
	int				i;

	i = -1;
	while (++i < lem->solve_count)
		move_path(lem, lem->paths[lem->solves[i]]);
}

// - TMP
STATIC void		spawn_lem(t_lem *lem)
{
	int				i;

	i = -1;
	while (++i < lem->solve_count && lem->start_room->ant > 0)
		if (lem->paths[lem->solves[i]].rooms[1]->ant == 0)
		{
			lem->start_room->ant--;
			lem->paths[lem->solves[i]].rooms[1]->ant = lem->ant_count - lem->start_room->ant;
			P(" L%d-%s", lem->paths[lem->solves[i]].rooms[1]->ant, lem->paths[lem->solves[i]].rooms[1]->name);
		}
}
// -

void			solve_lem(t_lem *lem)
{
	lem->start_room->ant = lem->ant_count;
	while (lem->end_room->ant < lem->ant_count)
	{
		move_lem(lem);
		spawn_lem(lem);
		NL;
	}
}
