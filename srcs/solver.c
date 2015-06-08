/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 12:50:55 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/08 18:16:30 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "solver.h"

STATIC void		move_ant(t_solver *solver, t_room *r1, t_room *r2)
{
	if (solver->first_tick)
		solver->first_tick = false;
	else
		PC(' ');
	P("L%d-%s", r1->ant, r2->name);
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

	solver->first_tick = true;
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

static int		ant_to_spawn(t_solver *solver)
{
	int				min_len;
	int				max_diff;
	int				sum_diff;
	int				i;

	min_len = solver->paths[0]->length;
	i = 0;
	while (++i < solver->path_count)
		if (solver->paths[i]->length < min_len)
			min_len = solver->paths[i]->length;
	sum_diff = solver->paths[0]->length - min_len;
	max_diff = sum_diff;
	i = 0;
	while (++i < solver->path_count)
	{
		if ((solver->paths[i]->length - min_len) > max_diff)
			max_diff = solver->paths[i]->length - min_len;
		sum_diff += solver->paths[i]->length - min_len;
	}
	return (solver->lem->ant_count - solver->next_ant
		- ((solver->path_count * max_diff) - sum_diff));
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
	solver = (t_solver){lem, paths, true, lem->solve_count, 0, lem->ant_count};
	while (solver.next_ant < lem->ant_count)
	{
		spawn_lem(&solver, ant_to_spawn(&solver));
		solver.path_count--;
	}
	while (solver.ants > 0)
		move_lem(&solver), PC('\n');
	FL;
}
