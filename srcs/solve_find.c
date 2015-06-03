/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 23:16:49 by juloo             #+#    #+#             */
/*   Updated: 2015/06/03 18:38:11 by jaguillo         ###   ########.fr       */
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

static int		solve_complexity(t_lem *lem, int *solve, int len)
{
	int				min;
	int				max;
	int				i;

	min = lem->paths[solve[0]].length;
	max = lem->paths[solve[0]].length;
	i = 0;
	while (++i < len)
		if (lem->paths[solve[i]].length < min)
			min = lem->paths[solve[i]].length;
		else if (lem->paths[solve[i]].length > max)
			max = lem->paths[solve[i]].length;
	max++;
	min++;
	min += (max - min + lem->ant_count + 1) / 2;
	// if (len == 1)
		// min = (lem->paths[solve[0]].length + lem->ant_count - 2);
	// min = (max - min + lem->ant_count + 1) / len + min;
	{
		int			i;
		int			j;

		P("%{gray}Complexity: (%d)", len);
		i = -1;
		while (++i < len)
		{
			if (i > 0)
				PS(", ");
			j = -1;
			while (++j < lem->paths[solve[i]].length)
				P(" %s", lem->rooms[lem->paths[solve[i]].rooms[j]].name);
		}
		P(" = %d", min), NL;
	}
	return (min);
}

STATIC void		solve_save(t_lem *lem, int *solve, int len)
{
	{
		int			i;
		int			j;

		P("%{gray}Test solution: (%d)\n", len);
		i = -1;
		while (++i < len)
		{
			j = -1;
			while (++j < lem->paths[solve[i]].length)
				P(" %s", lem->rooms[lem->paths[solve[i]].rooms[j]].name);
			NL;
		}
	}
	if (lem->solve_count < 0 || solve_complexity(lem, solve, len)
		< solve_complexity(lem, lem->solves, lem->solve_count))
	{
		ft_memcpy(lem->solves, solve, S(int, len));
		lem->solve_count = len;
		PS("SAVED"), NL;
	}
}

static void		track_solve(t_lem *lem, int path, int *solve, int len)
{
	solve[len++] = path;
	solve_save(lem, solve, len);
	while (++path < lem->path_count)
		if (!path_collide(lem, path, solve, len))
			track_solve(lem, path, solve, len);
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
