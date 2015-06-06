/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 18:03:27 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/06 02:42:54 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

STATIC void		set_friend(t_lem *lem, int room, char *friends)
{
	int				j;

	j = -1;
	while (++j < room)
		if (lem->links[room][j] && !(lem->rooms[j].flags & ROOM_FRIEND))
		{
			friends[j] = 1;
			lem->rooms[j].flags |= ROOM_FRIEND;
		}
		else
			friends[j] = 0;
	while (++j < lem->room_count)
		if (lem->links[j][room] && !(lem->rooms[j].flags & ROOM_FRIEND))
		{
			friends[j] = 1;
			lem->rooms[j].flags |= ROOM_FRIEND;
		}
		else
			friends[j] = 0;
}

STATIC void		unset_friend(t_lem *lem, char *friends)
{
	int				i;

	i = -1;
	while (++i < lem->room_count)
		if (friends[i])
			lem->rooms[i].flags &= ~(ROOM_FRIEND);
}

static void		track_path(t_lem *m, int room, t_room **path, int len, t_tab *a)
{
	int				j;
	char			friends[m->room_count];

	path[len++] = m->rooms + room;
	if (R_LINK(m->links, room, m->end_room_i))
	{
		path[len++] = m->rooms + m->end_room_i;
		ft_tabadd(a, &(t_path){ft_memdup(path, S(t_room*, len)), len});
		return ;
	}
	m->rooms[room].flags |= ROOM_PATH;
	set_friend(m, room, friends);
	j = -1;
	while (++j < room)
		if (friends[j] ||
			(m->links[room][j] && !(m->rooms[j].flags & (ROOM_PATH | ROOM_FRIEND))))
			track_path(m, j, path, len, a);
	while (++j < m->room_count)
		if (friends[j] ||
			(m->links[j][room] && !(m->rooms[j].flags & (ROOM_PATH | ROOM_FRIEND))))
			track_path(m, j, path, len, a);
	unset_friend(m, friends);
	m->rooms[room].flags &= ~(ROOM_PATH);
}

void			find_paths(t_lem *lem)
{
	t_tab			paths;
	t_room			*tmp_path[lem->room_count];

	ft_tabini(&paths, sizeof(t_path));
	track_path(lem, lem->start_room_i, tmp_path, 0, &paths);
	lem->paths = (t_path*)paths.data;
	lem->path_count = paths.length;
}
