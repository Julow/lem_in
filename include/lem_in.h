/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 19:19:36 by juloo             #+#    #+#             */
/*   Updated: 2015/06/09 14:36:41 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define STATIC		static inline

# define ERROR		"ERROR\n"

typedef struct	s_room
{
	char			*name;
	int				name_len;
	int				id;
	int				x;
	int				y;
	int				ant;
	int				flags;
}				t_room;

typedef struct	s_path
{
	t_room			**rooms;
	int				length;
}				t_path;

typedef struct	s_lem
{
	t_room			*rooms;
	int				room_count;
	t_room			*start_room;
	t_room			*end_room;
	char			**links;
	t_path			*paths;
	int				path_count;
	int				*solves;
	int				solve_ticks;
	int				solve_count;
	int				ant_count;
}				t_lem;

# define ROOM_START		(1 << 1)
# define ROOM_END		(1 << 2)
# define ROOM_PATH		(1 << 3)
# define ROOM_FRIEND	(1 << 4)

# define NOTHING		{}

# define R_LINK(l,a,b)	((a < b) ? l[b][a] : l[a][b])

# define TBEGIN(t,b)	((t*)((b).data))
# define TEND(t,b)		(TBEGIN(t, b) + (b).length)

void			find_paths(t_lem *lem);

t_bool			find_solves(t_lem *lem);

void			solve_lem(t_lem *lem);

void			print_lem(t_lem *lem);

t_bool			ft_subis(t_sub sub, t_is mask);
char			*ft_subdup(t_sub sub);
int				ft_subtoi(t_sub sub, int *nb);
t_bool			ft_subisint(t_sub sub);

#endif
