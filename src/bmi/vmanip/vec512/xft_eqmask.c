/* ************************************************************************** */
/*                                                                            */
/*                                                      :::      ::::::::     */
/*   xft_eqmask.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 11:06:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/07 11:36:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__always_inline__, const))
inline t_u64a	xft_veqmask512(t_vu512 vec, t_u8 b)
{
	return (__builtin_ia32_ucmpb512_mask((t_vc512)vec,
			(t_vc512)xft_vsplat512(b), 0, ~0ULL));
}

#endif
