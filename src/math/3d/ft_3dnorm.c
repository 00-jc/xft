/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3dnorm.c                                        :+:      :+:    :+:   */
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
inline t_8packd	ft_3dnorm8(t_3dcoordsx8 c)
{
	return (ft_dsqrt_x8(ft_3dclampsum8(ft_3dmul8(c, c))));
}

__attribute__((__always_inline__, const))
inline t_f64	ft_3dnorm(t_3dcoords c)
{
	t_v4da	vec;

	vec = *(const t_v4d * restrict const) & c;
	vec *= vec;
	return (ft_dsqrt(vec[0] + vec[1] + vec[2]));
}
