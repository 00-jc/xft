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

#if XFT_HAS_128_VEC

__attribute__((__always_inline__, const))
inline t_u16a	xft_rangemask128(t_vu128a v, t_u8 lo, t_u8 hi)
{
	return (xft_vmask128((t_vu128)(v - xft_vsplat128(lo)
			<= xft_vsplat128(hi - lo))));
}

#endif
