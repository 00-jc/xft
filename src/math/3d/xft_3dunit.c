/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_3dunit.c                                       :+:      :+:    :+:   */
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
inline t_3dcoords	xft_3dunit(const t_3dcoords *__restrict__ const c)
{
	t_v4da		v1;
	t_v4da		v2;

	v1 = *(const t_v4d * restrict const) c;
	v2 = v1;
	v1 *= v1;
	v2 *= xft_drsqrt(v1[0] + v1[1] + v1[2]);
	return (*(const t_3dcoords * restrict const) & v2);
}
