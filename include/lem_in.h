/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 19:19:36 by juloo             #+#    #+#             */
/*   Updated: 2015/05/31 02:15:45 by juloo            ###   ########.fr       */
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

typedef struct	s_lem
{
	t_room			*rooms;
	int				**links;
	int				length;
	int				ant_count;
}				t_lem;

typedef struct	s_path
{
	t_room			**room;
	int				length;
}				t_path;

# define ROOM_START		(1 << 1)
# define ROOM_END		(1 << 2)

void			print_lem(t_lem *lem);

t_bool			ft_subis(t_sub sub, t_is mask);

#endif
