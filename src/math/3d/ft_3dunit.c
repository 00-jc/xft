/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3dunit.c                                        :+:      :+:    :+:   */
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
inline t_8packd	ft_3dclampsum8(t_3dcoordsx8 c)
{
	t_v8da		v[4];

	v[0] = *(const t_v8d * restrict const) & c.a;
	v[1] = *(const t_v8d * restrict const) & c.c;
	v[2] = *(const t_v8d * restrict const) & c.e;
	v[3] = *(const t_v8d * restrict const) & c.g;
	return ((t_8packd)
		{
			.x = v[0][0] + v[0][1] + v[0][2],
			.y = v[0][4] + v[0][5] + v[0][6],
			.z = v[1][0] + v[1][1] + v[1][2],
			.w = v[1][4] + v[1][5] + v[1][6],
			.a = v[2][0] + v[2][1] + v[2][2],
			.b = v[2][4] + v[2][5] + v[2][6],
			.c = v[3][0] + v[3][1] + v[3][2],
			.d = v[3][4] + v[3][5] + v[3][6],
		});
}

__attribute__((__always_inline__, const))
inline t_3dcoordsx8	ft_3dunit8(t_3dcoordsx8 c)
{
	t_v8da			v[4];
	t_3dcoordsx8	sq;
	t_8packd		sums;
	t_8packd		inv;

	sq = ft_3dmul8(c, c);
	sums = ft_3dclampsum8(sq);
	inv = ft_drsqrt_x8(sums);
	v[0] = (*(const t_v8d * restrict const) & c.a)
		* (t_v8da){inv.x, inv.x, inv.x, 0, inv.y, inv.y, inv.y, 0};
	v[1] = (*(const t_v8d * restrict const) & c.c)
		* (t_v8da){inv.z, inv.z, inv.z, 0, inv.w, inv.w, inv.w, 0};
	v[2] = (*(const t_v8d * restrict const) & c.e)
		* (t_v8da){inv.a, inv.a, inv.a, 0, inv.b, inv.b, inv.b, 0};
	v[3] = (*(const t_v8d * restrict const) & c.g)
		* (t_v8da){inv.c, inv.c, inv.c, 0, inv.d, inv.d, inv.d, 0};
	return (*(const t_3dcoordsx8 * restrict const) & v);
}

__attribute__((__always_inline__, const))
inline t_3dcoords	ft_3dunit(t_3dcoords c)
{
	t_v4da		v1;
	t_v4da		v2;

	v1 = *(const t_v4d * restrict const ) & c;
	v2 = v1;
	v1 *= v1;
	v2 *= ft_drsqrt(v1[0] + v1[1] + v1[2]);
	return (*(const t_3dcoords * restrict const) & v2);
}
