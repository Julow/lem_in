/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 19:19:36 by juloo             #+#    #+#             */
/*   Updated: 2015/06/03 01:06:04 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define STATIC		static inline

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

typedef struct	s_solve
{
	int				*paths;
	int				length;
	int				sum;
}				t_solve;

typedef struct	s_lem
{
	t_room			*rooms;
	int				room_count;
	int				start_room;
	int				end_room;
	char			**links;
	t_path			*paths;
	int				path_count;
	t_solve			**solves;
	int				solve_count;
	int				ant_count;
}				t_lem;

# define ROOM_START		(1 << 1)
# define ROOM_END		(1 << 2)
# define ROOM_PATH		(1 << 3)

void			find_paths(t_lem *lem);

void			find_solves(t_lem *lem);
int				solve_cmp(t_solve *s1, t_solve *s2);

void			print_lem(t_lem *lem);

t_bool			ft_subis(t_sub sub, t_is mask);

#endif
