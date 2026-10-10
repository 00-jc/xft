/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_3dadd.c                                        :+:      :+:    :+:   */
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
inline t_3dcoords	xft_3dadd(const t_3dcoords *__restrict__ const a,
	const t_3dcoords *__restrict__ const b)
{
	t_v4da	vec;

	vec = *(const t_v4d * restrict const) a
		+ *(const t_v4d * restrict const) b;
	return (*(const t_4packd * restrict const) & vec);
}
