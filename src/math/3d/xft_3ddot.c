/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_3ddot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/07 21:56:35 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_math.h"
#include "math.h"

__attribute__((__always_inline__, pure, __used__))
inline t_8packd	xft_3ddot8(const t_3dcoordsx8 *__restrict__ const a,
	const t_3dcoordsx8 *__restrict__ const b)
{
	t_3dcoordsx8	res;

	res = xft_3dmul8(a, b);
	return (xft_3dclampsum8(&res));
}

__attribute__((__always_inline__, pure, __used__))
inline t_f64	xft_3ddot(const t_3dcoords *__restrict__ const a,
	const t_3dcoords *__restrict__ const b)
{
	t_v4da	va;
	t_v4da	vb;

	va = *(const t_v4d * restrict const) a;
	vb = *(const t_v4d * restrict const) b;
	va *= vb;
	return (va[0] + va[1] + va[2]);
}
