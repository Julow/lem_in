/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 16:45:46 by juloo             #+#    #+#             */
/*   Updated: 2015/06/07 17:16:53 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ft_subtoi
** ----
** Convert the content of sub to an int
** Same behavior as ft_atoib
** ----
** Return the length of the number (in the sub)
** or 0 if there is no
*/
int				ft_subtoi(t_sub sub, int *nb)
{
	int				i;
	t_bool			negative;

	*nb = 0;
	if (sub.length <= 0)
		return (0);
	negative = (sub.str[0] == '-') ? true : false;
	i = (sub.str[0] == '-' || sub.str[0] == '+') ? 1 : 0;
	while (sub.str[i] >= '0' && sub.str[i] <= '9')
		*nb = *nb * 10 + (sub.str[i++] - '0');
	if (negative)
		*nb = -(*nb);
	return (i);
}
