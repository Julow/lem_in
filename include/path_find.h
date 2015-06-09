/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 14:28:07 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/09 14:29:23 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_FIND_H
# define PATH_FIND_H

# include "lem_in.h"

# define PATH(p,l)		((t_path){(p), (l)})

typedef struct	s_finder
{
	t_lem			*lem;
	t_tab			paths;
}				t_finder;

#endif
