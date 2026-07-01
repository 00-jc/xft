/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3dcross.c                                       :+:      :+:    :+:   */
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
inline t_3dcoords	ft_3dcross(t_3dcoords a, t_3dcoords b)
{
	t_v4da	vec;
	t_v4da	vec1;

	vec = (t_v4da){a.y, a.z, a.x} * (t_v4da){b.z, b.x, b.y};
	vec1 = (t_v4da){a.z, a.x, a.y} * (t_v4da){b.y, b.z, b.x};
	vec -= vec1;
	return (*(const t_3dcoords * restrict const) & vec);
}
