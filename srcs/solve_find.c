/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 23:16:49 by juloo             #+#    #+#             */
/*   Updated: 2015/06/03 00:50:40 by juloo            ###   ########.fr       */
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

static int		solve_length(t_lem *lem, int *solve, int len)
{
	int				i;
	int				sum;

	sum = 0;
	i = -1;
	while (++i < len)
		sum += lem->paths[solve[i]].length;
	return (sum);
}

static void		track_solve(t_lem *m, int path, int *solve, int len, t_array *a)
{
	int				i;
	void			*tmp;

	solve[len++] = path;
	tmp = ft_emalloc(S(int, len) + sizeof(t_solve));
	ft_memcpy(tmp, &(t_solve){tmp + sizeof(t_solve), len,
		solve_length(m, solve, len)}, sizeof(t_solve));
	ft_memcpy(tmp + sizeof(t_solve), solve, S(int, len));
	ft_arrayadd(a, tmp);
	i = -1;
	while (++i < m->path_count)
		if (!path_collide(m, i, solve, len))
			track_solve(m, i, solve, len, a);
}

void			find_solves(t_lem *lem)
{
	t_array			solves;
	int				tmp_solve[lem->path_count];
	int				i;

	ft_arrayini(&solves);
	i = -1;
	while (++i < lem->path_count)
		track_solve(lem, i, tmp_solve, 0, &solves);
	lem->solves = (t_solve**)solves.data;
	lem->solve_count = solves.length;
}
