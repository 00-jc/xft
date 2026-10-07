/* ************************************************************************** */
/*                                                                            */
/*                                                      :::      ::::::::     */
/*   xft_rangemask.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 11:36:24 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/07 11:36:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_256_VEC

__attribute__((__always_inline__, const))
inline t_u32a	xft_rangemask256(t_vu256a v, t_u8 lo, t_u8 hi)
{
	return (xft_vmask256((t_vu256)(v - xft_vsplat256(lo)
			<= xft_vsplat256(hi - lo))));
}

#endif
