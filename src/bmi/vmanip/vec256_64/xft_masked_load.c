/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_masked_load.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 12:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_vu64_256a	xft_vmask_load256_64(t_cany ptr, t_u8 mask)
{
	return ((t_vu64_256a)__builtin_ia32_loaddqudi256_mask(ptr,
			(t_vs64_256){}, mask));
}

#elif XFT_HAS_256_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_vu64_256a	xft_vmask_load256_64(t_cany ptr, t_u8 mask)
{
	t_vs64_256	lanes;
	t_vs64_256	sel;

	lanes = (t_vs64_256)xft_vsplat256_64(mask);
	sel = (t_vs64_256)(xft_vsplat256_64(1) << xft_viota256_64());
	return ((t_vu64_256a)__builtin_ia32_maskloadq256(ptr,
			(t_vs64_256)((lanes & sel) != 0)));
}

#endif
