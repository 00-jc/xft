/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 00:49:19 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"
#include "math.h"

__attribute__((const, __always_inline__))
inline t_u64a	ft_tern(t_u64a cond, t_u64a value1, t_u64a value2)
{
	return ((-(cond) & value1) | (~(-cond) & value2));
}

__attribute__((const, __always_inline__))
inline t_f64	ft_dtern(t_u64a cond, t_f64 value1, t_f64 value2)
{
	t_dp	a;
	t_dp	b;

	a = (t_dp){.f = value1};
	b = (t_dp){.f = value2};
	return ((t_dp){.i = (-cond & a.i) | (~(-cond) & b.i)}.f);
}
