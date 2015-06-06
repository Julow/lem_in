/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 18:03:27 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/07 01:55:16 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

static t_bool	path_friend(t_lem *lem, int room, t_room **path, int len)
{
	int				i;

	i = -1;
	while (++i < len - 1)
		if (R_LINK(lem->links, room, path[i]->id))
			return (true);
	return (false);
}

static void		track_path(t_lem *m, int room, t_room **path, int len, t_tab *a)
{
	int				j;

	path[len++] = m->rooms + room;
	if (R_LINK(m->links, room, m->end_room->id))
	{
		path[len++] = m->end_room;
		ft_tabadd(a, &(t_path){ft_memdup(path, S(t_room*, len)), len});
		return ;
	}
	m->rooms[room].flags |= ROOM_PATH;
	j = -1;
	while (++j < room)
		if (m->links[room][j] && !(m->rooms[j].flags & ROOM_PATH)
			&& !path_friend(m, j, path, len))
			track_path(m, j, path, len, a);
	while (++j < m->room_count)
		if (m->links[j][room] && !(m->rooms[j].flags & ROOM_PATH)
			&& !path_friend(m, j, path, len))
			track_path(m, j, path, len, a);
	m->rooms[room].flags &= ~(ROOM_PATH);
}

void			find_paths(t_lem *lem)
{
	t_tab			paths;
	t_room			*tmp_path[lem->room_count];

	ft_tabini(&paths, sizeof(t_path));
	track_path(lem, lem->start_room->id, tmp_path, 0, &paths);
	lem->paths = (t_path*)paths.data;
	lem->path_count = paths.length;
}
