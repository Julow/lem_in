/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 18:03:27 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/09 14:34:50 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "path_find.h"

static t_bool	path_friend(t_lem *lem, int room, t_room **path, int len)
{
	int				i;

	i = -1;
	while (++i < len - 1)
		if (R_LINK(lem->links, room, path[i]->id))
			return (true);
	return (false);
}

static void		track_path(t_finder *f, int room, t_room **path, int len)
{
	int				j;

	path[len++] = f->lem->rooms + room;
	if (R_LINK(f->lem->links, room, f->lem->end_room->id))
	{
		path[len++] = f->lem->end_room;
		ft_tabadd(&(f->paths), &PATH(ft_memdup(path, S(t_room*, len)), len));
		return ;
	}
	f->lem->rooms[room].flags |= ROOM_PATH;
	j = -1;
	while (++j < room)
		if (f->lem->links[room][j] && !(f->lem->rooms[j].flags & ROOM_PATH)
			&& !path_friend(f->lem, j, path, len))
			track_path(f, j, path, len);
	while (++j < f->lem->room_count)
		if (f->lem->links[j][room] && !(f->lem->rooms[j].flags & ROOM_PATH)
			&& !path_friend(f->lem, j, path, len))
			track_path(f, j, path, len);
	f->lem->rooms[room].flags &= ~(ROOM_PATH);
}

void			find_paths(t_lem *lem)
{
	t_finder		find;
	t_room			*tmp_path[lem->room_count];

	find.lem = lem;
	ft_tabini(&(find.paths), sizeof(t_path));
	track_path(&find, lem->start_room->id, tmp_path, 0);
	lem->paths = (t_path*)find.paths.data;
	lem->path_count = find.paths.length;
}
