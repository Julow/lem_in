/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 23:35:15 by juloo             #+#    #+#             */
/*   Updated: 2015/06/03 19:16:49 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"

int				main(void)
{
	t_lem			lem;

	if (!parser(0, &lem))
		return (ft_fdprintf(2, ERROR), 1);
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
				P(" %s", lem.rooms[lem.paths[i].rooms[j]].name);
			NL;
		}
	}
// -
	if (!find_solves(&lem))
		return (ft_fdprintf(2, ERROR), 1);
	P("%{cyan}Solution: (%d)%{reset}", lem.solve_count), NL;
// print solves
	{
		int				j;
		int				k;

		j = -1;
		while (++j < lem.solve_count)
		{
			k = -1;
			while (++k < lem.paths[lem.solves[j]].length)
				P(" %s", lem.rooms[lem.paths[lem.solves[j]].rooms[k]].name);
			NL;
		}
	}
// -
	return (0);
}
