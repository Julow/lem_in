/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lambda.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 18:04:17 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/04 19:21:32 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LAMBDA_H
# define FT_LAMBDA_H

/*
** ========================================================================== **
** Lambda
** ----
** Example:
** -
**  void		for_each(int *data, int len, int (L func)(int))
**  {
**  	int			i;
** -
**  	i = -1;
**  	while (++i < len)
**  		data[i] = func(data[i]);
**  }
** -
**  int			main(void)
**  {
**  	int			test[] = {1, 2, 3, 4, 5, 6, 7, 8};
**  
**  	LAMBDA(int, pow2, int a);
**  	{ // Optionnal
**  		return (a * a);
**  	} // Optionnal
**  	LEND(pow2);
** -
**  	for_each(test, 8, pow2);
**  }
*/

# ifdef __clang__

#  define L							^
#  define LAMBDA(t, name, ...)		t (^name)() = ^t (__VA_ARGS__) {
#  define LEND(name)				}

# else

#  define L							*
#  define LAMBDA(t, name, ...)		t (*name)() = ({ t name(__VA_ARGS__) {
#  define LEND(name)				} name; })

# endif

#endif
