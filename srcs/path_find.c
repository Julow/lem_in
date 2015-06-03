/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 18:03:27 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/03 16:01:47 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

static t_bool	path_contains(t_path *big, t_path *small)
{
	int				i;
	int				j;
	int				max;

	if (big->length < small->length)
		return (path_contains(small, big));
	max = big->length - small->length;
	i = -1;
	while (++i < max)
	{
		j = 0;
		while (++j < (small->length - 1))
			if (big->rooms[i + j] != small->rooms[j])
				break ;
		if (j == small->length - 1)
			return (true);
	}
	return (false);
}

static void		add_path(int *path, int len, t_tab *all)
{
	int				i;
	t_path			curr;

	curr = (t_path){path, len};
	i = -1;
	while (++i < all->length)
		if (!path_contains(&curr, TG(t_path, *all, i)))
			continue ;
		else if (len > TG(t_path, *all, i)->length)
			return ;
		else if (len == TG(t_path, *all, i)->length)
			ft_fdprintf(2, "OMGLOL\n");
		else
		{
			free(TG(t_path, *all, i)->rooms);
			ft_tabrem(all, i--, 1);
		}
	curr.rooms = ft_memdup(path, S(int, len));
	ft_tabadd(all, &curr);
}

static void		track_path(t_lem *m, int room, int *path, int len, t_tab *all)
{
	int				j;

	path[len++] = room;
	if (room == m->end_room)
	{
		add_path(path, len, all);
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
