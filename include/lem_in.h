/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 19:19:36 by juloo             #+#    #+#             */
/*   Updated: 2015/06/02 19:00:33 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	int				ant;
	int				flags;
}				t_room;

typedef struct	s_path
{
	int				*rooms;
	int				length;
}				t_path;

typedef struct	s_lem
{
	t_room			*rooms;
	char			**links;
	int				room_count;
	int				start_room;
	int				end_room;
	int				ant_count;
	t_path			*paths;
	int				path_count;
}				t_lem;

# define ROOM_START		(1 << 1)
# define ROOM_END		(1 << 2)

void			find_paths(t_lem *lem);

void			print_lem(t_lem *lem);

t_bool			ft_subis(t_sub sub, t_is mask);

#endif
