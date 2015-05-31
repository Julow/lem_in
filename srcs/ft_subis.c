/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 02:01:37 by juloo             #+#    #+#             */
/*   Updated: 2015/05/31 02:02:35 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool			ft_subis(t_sub sub, t_is mask)
{
	int				i;

	i = -1;
	while (++i < sub.length)
		if (!IS(sub.str[i], mask))
			return (false);
	return (true);
}
