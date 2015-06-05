/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 14:32:24 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/06 00:57:34 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

# include "lem_in.h"

typedef struct	s_solver
{
	t_lem			*lem;
	t_path			**paths;
	int				path_count;
	int				next_ant;
	int				ants;
}				t_solver;

#endif
