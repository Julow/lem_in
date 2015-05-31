/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 23:26:24 by juloo             #+#    #+#             */
/*   Updated: 2015/05/31 02:10:34 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"
#include <stdlib.h>

static t_bool	build_links(t_lem *lem, t_lem_raw *raw)
{
	int				i;
	t_raw_link		*tmp;

	if (lem->length <= 0 || raw->links.length <= 0)
		return (false);
	lem->links = MAL(int*, lem->length);
	i = -1;
	while (++i < lem->length)
	{
		lem->links[i] = MAL(int, i);
		ft_bzero(lem->links[i], S(int, i));
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
	int				flags;
	int				i;

	lem->rooms = (t_room*)raw->rooms.data;
	lem->length = raw->rooms.length;
	i = -1;
	flags = 0;
	while (++i < lem->length)
		if (lem->rooms[i].flags & flags)
			return (false);
		else
			flags |= lem->rooms[i].flags;
	if ((flags & ROOM_START) && (flags & ROOM_END))
		return (true);
	return (false);
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
