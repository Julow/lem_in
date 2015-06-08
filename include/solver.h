/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 14:32:24 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/08 18:14:21 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

# include "lem_in.h"

typedef struct	s_solver
{
	t_lem			*lem;
	t_path			**paths;
	t_bool			first_tick;
	int				path_count;
	int				next_ant;
	int				ants;
}				t_solver;

int				path_cmp(t_path *p1, t_path *p2);

#endif
