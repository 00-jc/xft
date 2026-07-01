/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3ddot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_math.h"
#include "math.h"

__attribute__((__always_inline__, const))
inline t_8packd	ft_3ddot8(t_3dcoordsx8 a, t_3dcoordsx8 b)
{
	t_3dcoordsx8	res;

	res = ft_3dmul8(a, b);
	return (ft_3dclampsum8(res));
}

__attribute__((__always_inline__, const))
inline t_f64	ft_3ddot(t_3dcoords a, t_3dcoords b)
{
	t_v4da	va;
	t_v4da	vb;

	va = *(const t_v4d * restrict const) & a;
	vb = *(const t_v4d * restrict const) & b;
	va *= vb;
	return (va[0] + va[1] + va[2]);
}
