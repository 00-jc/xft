/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_3dmul.c                                        :+:      :+:    :+:   */
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
inline t_3dcoordsx8	xft_3dmul8(const t_3dcoordsx8 *__restrict__ const a,
	const t_3dcoordsx8 *__restrict__ const b)
{
	t_v8da	vec[4];

	vec[0] = *(const t_v8d * restrict const) & a->a
		* *(const t_v8d * restrict const) & b->a;
	vec[1] = *(const t_v8d * restrict const) & a->c
		* *(const t_v8d * restrict const) & b->c;
	vec[2] = *(const t_v8d * restrict const) & a->e
		* *(const t_v8d * restrict const) & b->e;
	vec[3] = *(const t_v8d * restrict const) & a->g
		* *(const t_v8d * restrict const) & b->g;
	return (*(const t_3dcoordsx8 * restrict const) & vec);
}

__attribute__((__always_inline__, pure, __used__))
inline t_3dcoords	xft_3dmul(const t_3dcoords *__restrict__ const a,
	const t_3dcoords *__restrict__ const b)
{
	t_v4da	vec;

	vec = *(const t_v4d * restrict const) a
		* *(const t_v4d * restrict const) b;
	return (*(const t_4packd * restrict const) & vec);
}
