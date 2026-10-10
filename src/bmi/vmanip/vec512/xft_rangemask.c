/* ************************************************************************** */
/*                                                                            */
/*                                                      :::      ::::::::     */
/*   xft_rangemask.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 11:13:52 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/07 11:36:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__always_inline__, const, __used__))
inline t_u64a	xft_rangemask512(t_vu512a v, t_u8 lo, t_u8 hi)
{
	return (xft_vmask512((t_vu512)(v - xft_vsplat512(lo)
			<= xft_vsplat512(hi - lo))));
}

#endif
