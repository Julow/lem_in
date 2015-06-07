/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 23:26:24 by juloo             #+#    #+#             */
/*   Updated: 2015/06/07 18:19:29 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"
#include <stdlib.h>

static t_bool	parse_links(t_parser *parser, t_sub line)
{
	int				a;
	int				b;

	line.length = 0;
	if (!ft_subnextc(&line, '-'))
		return (false);
	if ((a = room_index(parser, line)) < 0)
		return (false);
	if (!ft_subnextc(&line, '-'))
		return (false);
	if ((b = room_index(parser, line)) < 0)
		return (false);
	if (ft_subnextc(&line, '-'))
		return (false);
	if (a > b)
		parser->links[a][b] = 1;
	else
		parser->links[b][a] = 1;
	return (true);
}

static t_bool	init_links(t_parser *parser, t_sub line)
{
	int				i;

	parser->f = &parse_links;
	parser->links = MAL(char*, parser->rooms.length);
	i = -1;
	while (++i < parser->rooms.length)
	{
		parser->links[i] = MAL(char, i);
		ft_bzero(parser->links[i], S(char, i));
	}
	return (parse_links(parser, line));
}

static t_bool	parse_rooms(t_parser *parser, t_sub line)
{
	t_room			tmp;

	if (ft_strequ(line.str, "##start"))
		return ((parser->flags = ROOM_START), true);
	if (ft_strequ(line.str, "##end"))
		return ((parser->flags = ROOM_END), true);
	if (ft_subcount(line, ~IS_SPACE) != 3)
		return (init_links(parser, line));
	line.length = 0;
	ft_subnext(&line, IS_SPACE);
	tmp = (t_room){ft_subdup(line), line.length, 0, 0, 0, 0, parser->flags};
	parser->flags = 0;
	ft_subnext(&line, IS_SPACE);
	if (!ft_subtoi(line, &(tmp.x)))
		return (false);
	ft_subnext(&line, IS_SPACE);
	if (!ft_subtoi(line, &(tmp.y)))
		return (false);
	tmp.id = parser->rooms.length;
	ft_tabadd(&(parser->rooms), &tmp);
	if ((tmp.flags & ROOM_START) && parser->start_room < 0)
		parser->start_room = tmp.id;
	else if ((tmp.flags & ROOM_END) && parser->end_room < 0)
		parser->end_room = tmp.id;
	return (true);
}

static t_bool	parse_ant_count(t_parser *parser, t_sub line)
{
	if (!ft_subisint(line))
		return (false);
	if (!ft_subtoi(line, &(parser->ant_count)))
		return (false);
	parser->f = &parse_rooms;
	return (true);
}

t_bool			parser(int fd, t_lem *lem)
{
	t_parser		parser;
	t_sub			line;

	parser = (t_parser){{}, NULL, -1, -1, 0, 0, &parse_ant_count};
	ft_tabini(&(parser.rooms), sizeof(t_room));
	while (get_next_line(fd, &line) > 0)
	{
		ft_subtrim(&line, IS_SPACE);
		if (line.str[0] == '#' && line.str[1] != '#')
			continue ;
		if (line.length <= 0 || !parser.f(&parser, line))
			return (false);
	}
	lem->rooms = (t_room*)parser.rooms.data;
	lem->room_count = parser.rooms.length;
	lem->start_room = lem->rooms + parser.start_room;
	lem->end_room = lem->rooms + parser.end_room;
	lem->links = parser.links;
	lem->ant_count = parser.ant_count;
	return (true);
}
