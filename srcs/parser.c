/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 23:26:24 by juloo             #+#    #+#             */
/*   Updated: 2015/06/04 18:51:22 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"
#include <stdlib.h>

static t_bool	build_links(t_lem *lem, t_lem_raw *raw)
{
	int				i;
	t_raw_link		*tmp;

	if (lem->room_count <= 0 || raw->links.length <= 0)
		return (false);
	lem->links = MAL(char*, lem->room_count);
	i = -1;
	while (++i < lem->room_count)
	{
		lem->links[i] = MAL(char, i);
		ft_bzero(lem->links[i], S(char, i));
	}
	i = -1;
	while (++i < raw->links.length)
	{
		tmp = TG(t_raw_link, raw->links, i);
		if (tmp->a > tmp->b)
			lem->links[tmp->a][tmp->b] = 1;
		else if (tmp->a < tmp->b)
			lem->links[tmp->b][tmp->a] = 1;
	}
	free(raw->links.data);
	return (true);
}

static t_bool	build_rooms(t_lem *lem, t_lem_raw *raw)
{
	int				i;

	lem->rooms = (t_room*)raw->rooms.data;
	lem->room_count = raw->rooms.length;
	lem->start_room = NULL;
	lem->end_room = NULL;
	i = -1;
	while (++i < lem->room_count)
		if (lem->rooms[i].flags & ROOM_START)
		{
			if (lem->start_room != NULL)
				return (false);
			lem->start_room_i = i;
			lem->start_room = lem->rooms + i;
		}
		else if (lem->rooms[i].flags & ROOM_END)
		{
			if (lem->end_room != NULL)
				return (false);
			lem->end_room_i = i;
			lem->end_room = lem->rooms + i;
		}
	if (lem->start_room == NULL || lem->end_room == NULL)
		return (false);
	return (true);
}

t_bool			parser(int fd, t_lem *lem)
{
	t_lem_raw		raw;

	ft_tabini(&(raw.rooms), sizeof(t_room));
	ft_tabini(&(raw.links), sizeof(t_raw_link));
	parse_raw(fd, &raw);
	lem->ant_count = raw.ant_count;
	if (!build_rooms(lem, &raw) || !build_links(lem, &raw))
		return (false);
	return (true);
}
