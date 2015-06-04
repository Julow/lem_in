/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 12:50:55 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/04 14:32:27 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

STATIC void		move_path(t_lem *lem, t_path path)
{
	int				i;

	i = path.length - 1;
	while (--i > 0)
		if (lem->rooms[path.rooms[i]].ant != 0)
		{
			if (path.rooms[i + 1] == lem->end_room)
				lem->rooms[lem->end_room].ant++;
			else if (lem->rooms[path.rooms[i + 1]].ant != 0)
				PS(" CONFLICT:");
			else
				lem->rooms[path.rooms[i + 1]].ant = lem->rooms[path.rooms[i]].ant;
			P(" L%d-%s", lem->rooms[path.rooms[i]].ant, lem->rooms[path.rooms[i + 1]].name);
			lem->rooms[path.rooms[i]].ant = 0;
		}
}

static void		move_lem(t_lem *lem)
{
	int				i;

	i = -1;
	while (++i < lem->solve_count)
		move_path(lem, lem->paths[lem->solves[i]]);
}

// - TMP
static void		spawn_lem(t_lem *lem)
{
	int				i;

	i = -1;
	while (++i < lem->solve_count && lem->rooms[lem->start_room].ant > 0)
		if (lem->rooms[lem->paths[lem->solves[i]].rooms[1]].ant == 0)
		{
			lem->rooms[lem->paths[lem->solves[i]].rooms[1]].ant = lem->rooms[lem->start_room].ant;
			P(" L%d-%s", lem->rooms[lem->start_room].ant--, lem->rooms[lem->paths[lem->solves[i]].rooms[1]].name);
		}
}
// -

void			solve_lem(t_lem *lem)
{
	lem->rooms[lem->start_room].ant = lem->ant_count;
	while (lem->rooms[lem->end_room].ant < lem->ant_count)
	{
		move_lem(lem);
		spawn_lem(lem);
		NL;
	}
}
