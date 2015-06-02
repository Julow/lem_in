/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 18:03:27 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/02 23:08:21 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		track_path(t_lem *m, int room, int *path, int len, t_tab *all)
{
	int				j;

	path[len++] = room;
	if (room == m->end_room)
	{
		ft_tabadd(all, &(t_path){ft_memdup(path, S(int, len)), len});
		return ;
	}
	m->rooms[room].flags |= ROOM_PATH;
	j = -1;
	while (++j < room)
		if (m->links[room][j] && !(m->rooms[j].flags & ROOM_PATH))
			track_path(m, j, path, len, all);
	while (++j < m->room_count)
		if (m->links[j][room] && !(m->rooms[j].flags & ROOM_PATH))
			track_path(m, j, path, len, all);
	m->rooms[room].flags &= ~(ROOM_PATH);
}

void			find_paths(t_lem *lem)
{
	t_tab			paths;
	int				tmp_path[lem->room_count];

	ft_tabini(&paths, sizeof(t_path));
	track_path(lem, lem->start_room, tmp_path, 0, &paths);
	lem->paths = (t_path*)paths.data;
	lem->path_count = paths.length;
}
