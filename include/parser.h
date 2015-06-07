/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 23:24:59 by juloo             #+#    #+#             */
/*   Updated: 2015/06/07 22:12:23 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lem_in.h"

typedef struct	s_parser
{
	t_tab			rooms;
	char			**links;
	int				start_room;
	int				end_room;
	int				flags;
	int				ant_count;
	t_bool			(*f)(struct s_parser *, t_sub);
}				t_parser;

/*
** Init and fill t_lem struct
*/
t_bool			parser(int fd, t_lem *lem);

/*
** Private
*/
int				room_index(t_parser *parser, t_sub name);

#endif
