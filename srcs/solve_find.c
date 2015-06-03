/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 23:16:49 by juloo             #+#    #+#             */
/*   Updated: 2015/06/03 11:38:02 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

STATIC t_bool	path_collide(t_lem *m, int path, int *solve, int len)
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

STATIC void		solve_save(t_lem *m, int *solve, int len, t_array *a)
{
	int				i;
	int				sum;
	void			*tmp;

	sum = 0;
	i = -1;
	while (++i < len)
		sum += m->paths[solve[i]].length;
	i = -1;
	while (++i < a->length)
		if (solve_cmp(AG(t_solve*, a, i), &(t_solve){NULL, len, sum}) == 0)
			return ;
	tmp = ft_emalloc(S(int, len) + sizeof(t_solve));
	*((t_solve*)tmp) = (t_solve){tmp + sizeof(t_solve), len, sum};
	ft_memcpy(tmp + sizeof(t_solve), solve, S(int, len));
	ft_arrayadd(a, tmp);
}

static void		track_solve(t_lem *m, int path, int *solve, int len, t_array *a)
{
	int				i;

	solve[len++] = path;
	solve_save(m, solve, len, a);
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
