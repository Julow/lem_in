/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 12:50:55 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/08 14:49:00 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "solver.h"

STATIC void		move_ant(t_solver *solver, t_room *r1, t_room *r2)
{
	if (r2->ant != 0)
		PS(" %{red}CONFLICT%{reset}"); // NEVER
	P(" L%d-%s", r1->ant, r2->name);
	if (r2->flags & ROOM_END)
		solver->ants--;
	else
		r2->ant = r1->ant;
	r1->ant = 0;
}

static void		move_lem(t_solver *solver)
{
	int				i;
	int				j;

	i = -1;
	while (++i < solver->lem->solve_count)
	{
		j = solver->paths[i]->length - 1;
		while (--j >= 0)
			if (solver->paths[i]->rooms[j]->ant != 0)
				move_ant(solver, solver->paths[i]->rooms[j],
					solver->paths[i]->rooms[j + 1]);
	}
}

STATIC void		spawn_lem(t_solver *solver, int spawn)
{
	int				i;

	while (spawn > 0)
	{
		move_lem(solver);
		i = -1;
		while (++i < solver->path_count && spawn > 0)
		{
			solver->lem->start_room->ant = ++solver->next_ant;
			move_ant(solver, solver->lem->start_room,
				solver->paths[i]->rooms[1]);
			spawn--;
		}
		PC('\n');
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
	solver = (t_solver){lem, paths, lem->solve_count, 0, lem->ant_count};
	spawn_lem(&solver, lem->ant_count);
	while (solver.ants > 0)
		move_lem(&solver), PC('\n');
	FL;
}
