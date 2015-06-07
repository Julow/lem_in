/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 17:29:07 by juloo             #+#    #+#             */
/*   Updated: 2015/06/07 22:31:53 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				room_index(t_parser *parser, t_sub name)
{
	t_room			*it;
	t_room			*end;

	it = TBEGIN(t_room, parser->rooms) - 1;
	end = TEND(t_room, parser->rooms);
	while (++it < end)
		if (it->name_len == name.length
			&& ft_memcmp(it->name, name.str, name.length) == 0)
			return (it->id);
	return (-1);
}
