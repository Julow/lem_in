/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 23:35:15 by juloo             #+#    #+#             */
/*   Updated: 2015/06/08 18:12:58 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"

int				main(void)
{
	t_lem			lem;

	if (!parser(0, &lem))
		return (ft_fdprintf(2, ERROR), 1);
	find_paths(&lem);
	if (!find_solves(&lem))
		return (ft_fdprintf(2, ERROR), 1);
	print_lem(&lem);
	solve_lem(&lem);
	return (0);
}
