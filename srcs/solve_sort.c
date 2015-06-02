/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 00:07:46 by juloo             #+#    #+#             */
/*   Updated: 2015/06/03 00:49:29 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				solve_cmp(t_solve *s1, t_solve *s2)
{
	if (s1->length != s2->length)
		return (-(s1->length - s2->length));
	return (s1->sum - s2->sum);
}