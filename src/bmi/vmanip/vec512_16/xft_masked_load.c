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

#include <xft/types/xft_p_vmanip_types.h>

#if XFT_HAS_512_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__,
	__always_inline__, __flatten__, __used__))
inline t_vu16_512a	xft_vmask_load512_16(t_cany ptr, t_u32a mask)
{
	return ((t_vu16_512a)__builtin_ia32_loaddquhi512_mask(ptr,
			(t_vs16_512){}, mask));
}

#endif
