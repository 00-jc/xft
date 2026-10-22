/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_masked_load.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:02:20 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 13:55:39 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_vu512a	xft_vmask_load512(t_cany ptr, t_u64a mask)
{
	return ((t_vu512a)__builtin_ia32_loaddquqi512_mask(ptr,
			(t_vc512)xft_vsplat512(0), mask));
}

#endif
