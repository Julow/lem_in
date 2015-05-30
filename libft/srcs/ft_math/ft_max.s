;; ************************************************************************** ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_max.s                                           :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/01/24 11:31:57 by jaguillo          #+#    #+#             ;;
;;   Updated: 2015/01/24 11:33:42 by jaguillo         ###   ########.fr       ;;
;;                                                                            ;;
;; ************************************************************************** ;;

; int			ft_max(int a, int b);
global	ft_max

ft_max:
	cmp		rdi, rsi
	jg		.g
	mov		rax, rsi
	ret
.g:
	mov		rax, rdi
	ret
