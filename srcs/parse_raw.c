/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_raw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 23:35:39 by juloo             #+#    #+#             */
/*   Updated: 2015/06/07 01:30:14 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"

static int		room_index(t_lem_raw *raw, t_sub name)
{
	int				i;

	i = -1;
	while (++i < raw->rooms.length)
		if (ft_strlen(TG(t_room, raw->rooms, i)->name) == (t_uint)name.length
			&& ft_memcmp(TG(t_room, raw->rooms, i)->name, name.str,
				name.length) == 0)
			return (i);
	return (-1);
}

static t_bool	parse_raw_room(t_lem_raw *raw, t_sub line, int flags)
{
	t_sub			name;
	t_room			room;

	room = (t_room){NULL, 0, 0, 0, 0, flags & (ROOM_START | ROOM_END)};
	line.length = 0;
	ft_subnext(&line, IS_SPACE);
	if (line.length <= 0 || ft_strchr(line.str, '-') != NULL)
		return (false);
	name = line;
	ft_subnext(&line, IS_SPACE);
	if (line.length <= 0 || !ft_subis(line, IS_DIGIT))
		return (false);
	room.x = ft_atoi(line.str);
	ft_subnext(&line, IS_SPACE);
	if (line.length <= 0 || !ft_subis(line, IS_DIGIT))
		return (false);
	room.y = ft_atoi(line.str);
	room.name = ft_strndup(name.str, name.length);
	ft_tabadd(&(raw->rooms), &room);
	return (true);
}

static t_bool	parse_raw_link(t_lem_raw *raw, t_sub line)
{
	t_raw_link		link;

	if ((line.length = ft_strchri(line.str, '-')) < 0)
		return (false);
	if ((link.a = room_index(raw, line)) < 0)
		return (false);
	line.str += line.length + 1;
	line.length = ft_strlen(line.str);
	if ((link.b = room_index(raw, line)) < 0)
		return (false);
	ft_tabadd(&(raw->links), &link);
	return (true);
}

void			parse_raw(int fd, t_lem_raw *raw)
{
	t_sub			line;
	int				state;

	if (get_next_line(fd, &line) <= 0 || !ft_sisint(line.str))
		return ;
	raw->ant_count = ft_atoi(line.str);
	state = PARSE_ROOM;
	while (get_next_line(fd, &line) > 0 && line.length > 0)
		if (line.str[0] == '#')
		{
			if (ft_strequ(line.str, "##start"))
				state |= ROOM_START;
			else if (ft_strequ(line.str, "##end"))
				state |= ROOM_END;
		}
		else if (!(state & PARSE_ROOM) || !parse_raw_room(raw, line, state))
		{
			if (!parse_raw_link(raw, line))
				return ;
			state = PARSE_LINK;
		}
		else
			state = PARSE_ROOM;
}
