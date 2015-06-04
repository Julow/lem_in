/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 23:16:49 by juloo             #+#    #+#             */
/*   Updated: 2015/06/05 01:03:21 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	path_collide(t_lem *m, int path, int *solve, int len)
{
	int				i;
	int				j;
	int				k;

	i = -1;
	while (++i < len)
	{
		j = 0;
		while (++j < (m->paths[solve[i]].length - 1))
		{
			k = 0;
			while (++k < (m->paths[path].length - 1))
				if (m->paths[solve[i]].rooms[j]
					== m->paths[path].rooms[k])
					return (true);
		}
	}
	return (false);
}

// - TMP

// FLOOR((ant_count - (((SUM / AVERAGE) * MAX) - SUM)) / (SUM / AVERAGE)) + MAX + MIN

STATIC int		solve_ticks(t_lem *lem, int *solve, int len)
{
	int				sum;
	int				average;
	int				min;
	int				max;
	int				i;

	sum = lem->paths[solve[0]].length - 1;
	max = sum;
	min = sum;
	i = 0;
	while (++i < len)
	{
		if (lem->paths[solve[i]].length - 1 > max)
			max = lem->paths[solve[i]].length - 1;
		else if (lem->paths[solve[i]].length - 1 < min)
			min = lem->paths[solve[i]].length - 1;
		sum += lem->paths[solve[i]].length - 1;
	}
	average = sum / len;
	average = sum / average;
	return (((lem->ant_count - (average * max - sum) + 1) / average) + max + min);
}
// -

static void		solve_save(t_lem *lem, int *solve, int len)
{
	int				ticks;

	{
		int			i;
		int			j;

		P("%{gray}Test solution: (%d)\n", len);
		i = -1;
		while (++i < len)
		{
			j = -1;
			while (++j < lem->paths[solve[i]].length)
				P(" %s", lem->paths[solve[i]].rooms[j]->name);
			NL;
		}
	}
	ticks = solve_ticks(lem, solve, len);
	P(" TICKS: %d", ticks);
	if (lem->solve_count < 0 || ticks < lem->solve_ticks)
	{
		ft_memcpy(lem->solves, solve, S(int, len));
		lem->solve_count = len;
		lem->solve_ticks = ticks;
		PS(" SAVED");
	}
	NL;
}

static void		track_solve(t_lem *lem, int path, int *solve, int len)
{
	solve[len++] = path;
	while (++path < lem->path_count)
		if (!path_collide(lem, path, solve, len))
			track_solve(lem, path, solve, len);
	solve_save(lem, solve, len);
}

t_bool			find_solves(t_lem *lem)
{
	int				tmp_best[lem->path_count];
	int				tmp_solve[lem->path_count];
	int				i;

	lem->solves = tmp_best;
	lem->solve_count = -1;
	i = -1;
	while (++i < lem->path_count)
		track_solve(lem, i, tmp_solve, 0);
	if (lem->solve_count < 0)
		return (false);
	lem->solves = ft_memdup(tmp_best, S(int, lem->solve_count));
	return (true);
}
