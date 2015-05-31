/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 23:24:59 by juloo             #+#    #+#             */
/*   Updated: 2015/05/31 01:10:27 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lem_in.h"

typedef struct	s_lem_raw
{
	t_tab			rooms;
	t_tab			links;
	int				ant_count;
}				t_lem_raw;

typedef struct	s_raw_link
{
	int				a;
	int				b;
}				t_raw_link;

# define PARSE_ROOM		(1 << 16)
# define PARSE_LINK		(1 << 17)

/*
** Init and fill t_lem struct
*/
t_bool			parser(int fd, t_lem *lem);

/*
** Private
*/
void			parse_raw(int fd, t_lem_raw *raw);

#endif
