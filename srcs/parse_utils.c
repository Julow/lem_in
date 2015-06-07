/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 17:29:07 by juloo             #+#    #+#             */
/*   Updated: 2015/06/07 17:29:19 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				room_index(t_parser *parser, t_sub name)
{
	int				i;

	i = -1;
	while (++i < parser->rooms.length)
		if (TG(t_room, parser->rooms, i)->name_len == name.length
			&& ft_memcmp(TG(t_room, parser->rooms, i)->name, name.str,
				name.length) == 0)
			return (i);
	return (-1);
}
