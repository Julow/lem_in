/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 16:43:59 by juloo             #+#    #+#             */
/*   Updated: 2015/06/07 16:57:31 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ft_subdup
** ----
** Copy the content of sub into a new allocated string
** ----
** Return the new string
*/
char			*ft_subdup(t_sub sub)
{
	char			*dup;

	dup = MAL(char, sub.length + 1);
	ft_memcpy(dup, sub.str, sub.length);
	dup[sub.length] = '\0';
	return (dup);
}
