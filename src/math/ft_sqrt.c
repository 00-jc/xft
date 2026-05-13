/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 04:38:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

#ifdef __x86_64__

__attribute__((__always_inline__, const))
inline t_f32	ft_sqrt(t_f32 number)
{
	__asm__("sqrtss %1, %0" : "=x"(number) : "x"(number));
	return (number);
}

__attribute__((__always_inline__, const))
inline t_f64	ft_dsqrt(t_f64 number)
{
	__asm__("sqrtsd %1, %0" : "=x"(number) : "x"(number));
	return (number);
}

#else

__attribute__((__always_inline__, const))
inline t_f32	ft_sqrt(t_f32 number)
{
	return (ft_q_sqrt(number));
}

__attribute__((__always_inline__, const))
inline t_f64	ft_dsqrt(t_f64 number)
{
	return (ft_q_dsqrt(number));
}

#endif
