/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 23:35:15 by juloo             #+#    #+#             */
/*   Updated: 2015/06/02 19:00:09 by jaguillo         ###   ########.fr       */
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
// print paths
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
// -
	return (0);
}
