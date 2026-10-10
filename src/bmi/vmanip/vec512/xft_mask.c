/* ************************************************************************** */
/*                                                                            */
/*                                                      :::      ::::::::     */
/*   xft_mask.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 11:22:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/07 11:36:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__always_inline__, const, __used__))
inline t_u64a	xft_vmask512(t_vu512 vec)
{
	return (__builtin_ia32_cvtb2mask512((t_vc512)vec));
}

#endif
