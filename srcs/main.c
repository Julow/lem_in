/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 23:35:15 by juloo             #+#    #+#             */
/*   Updated: 2015/06/03 01:10:21 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"

int				main(void)
{
	t_lem			lem;

	if (!parser(0, &lem))
		return (ft_fdprintf(2, "ERROR\n"), 1);
	print_lem(&lem);
	find_paths(&lem);
	P("%{cyan}Paths: (%d)%{reset}", lem.path_count), NL;
// print paths
	{
		int				i;
		int				j;

		i = -1;
		while (++i < lem.path_count)
		{
			j = -1;
			while (++j < lem.paths[i].length)
				P(" %d", lem.paths[i].rooms[j]);
			NL;
		}
	}
// -
	find_solves(&lem);
	ft_quicksort((void**)lem.solves, lem.solve_count, &solve_cmp);
	P("%{cyan}Solutions: (%d)%{reset}", lem.solve_count), NL;
// print solves
	{
		int				i;
		int				j;
		int				k;

		i = -1;
		while (++i < lem.solve_count)
		{
			P("%{green}Solution #%d (%d - %d):%{reset}",
				i, lem.solves[i]->length, lem.solves[i]->sum), NL;
			j = -1;
			while (++j < lem.solves[i]->length)
			{
				k = -1;
				while (++k < lem.paths[lem.solves[i]->paths[j]].length)
					P(" %d", lem.paths[lem.solves[i]->paths[j]].rooms[k]);
				NL;
			}
		}
	}
// -
	return (0);
}
