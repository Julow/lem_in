/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subisint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 16:59:18 by juloo             #+#    #+#             */
/*   Updated: 2015/06/07 17:08:08 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define MIN_INT_STR		"-2147483648"
#define MAX_INT_STR		"2147483647"

/*
** ft_subisint
** ----
** Test if sub is a valid int
** ----
** Return true if sub is a valid int
** false otherwise
*/
t_bool			ft_subisint(t_sub sub)
{
	int				i;

	if (sub.length <= 0 || sub.length > 11)
		return (false);
	i = (sub.str[0] == '-') ? 0 : -1;
	if (i == -1 && sub.length > 10)
		return (false);
	while (++i < sub.length)
		if (!IS(sub.str[i], IS_DIGIT))
			return (false);
	if (sub.str[0] == '-' && sub.length == 11
		&& ft_memcmp(sub.str, MIN_INT_STR, 11) > 0)
		return (false);
	if (sub.str[0] != '-' && sub.length == 10
		&& ft_memcmp(sub.str, MAX_INT_STR, 10) > 0)
		return (false);
	return (true);
}
