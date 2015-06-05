/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 12:50:55 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/05 18:38:27 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "solver.h"

static int		path_cmp(t_path *p1, t_path *p2)
{
	return (p1->length - p2->length);
}

static void		move_ant(t_solver *solver, t_room *r1, t_room *r2)
{
	if (r2->flags & ROOM_END)
		solver->ants--;
	else if (r2->ant != 0)
		PS(" CONFLICT"); // NEVER
	else
	{
		P(" L%d-%s", r2->name);
		r2->ant = r1->ant;
	}
	r1->ant = 0;
}

static void		move_lem(t_solver *solver)
{
	int				i;
	int				j;

	i = -1;
	while (++i < solver->path_count)
	{
		j = solver->paths[i]->length - 1;
		while (--j >= 0)
			if (solver->paths[i]->rooms[j]->ant != 0)
				move_ant(solver->paths[i]->rooms[j],
					solver->paths[i]->rooms[j - 1]);
	}
}

static void		spawn_lem(t_solver *solver, int spawn)
{
	int				i;

	while (spawn > 0)
	{
		i = -1;
		while (++i < solver->path_count)
		{
			// TODO
		}
		spawn--;
		solver->ants--;
		(void)solver;
	}
}

void			solve_lem(t_lem *lem)
{
	t_solver		solver;
	t_path			*paths[lem->solve_count];
	int				i;

	i = -1;
	while (++i < lem->solve_count)
		paths[i] = lem->paths + lem->solves[i];
	ft_quicksort((void**)paths, lem->solve_count, &path_cmp);
	solver = (t_solver){lem, paths, lem->solve_count, 0, lem->ant_count};
	while (solver.ants > 0)
	{
		i = solver.path_count * solver.paths[solver.path_count - 1]->length;
		if (solver.path_count > 1 && i > solver.ants)
		{
			solver.path_count--;
			continue ;
		}
		spawn_lem(&solver, MIN(i, solver.ants));
	}
}
