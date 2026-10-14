/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_compress_mask.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 16:59:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 20:00:58 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_vu512	xft_vcompress512(t_vu512a vec, t_u64a mask)
{
	return ((t_vu512)__builtin_ia32_compressqi512_mask((t_vc512)vec,
			(t_vc512)xft_vsplat512(0), mask));
}

#endif
