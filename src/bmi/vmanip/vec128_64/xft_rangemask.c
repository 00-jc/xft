/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_rangemask.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 12:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/types/xft_p_vmanip_types.h>

#if XFT_HAS_128_VEC

__attribute__((__always_inline__, __flatten__, const, __used__))
inline t_u8	xft_vrangemask128_64(t_vu64_128a v, t_u64 lo, t_u64 hi)
{
	return (xft_vmask128_64((t_vu64_128)(v - xft_vsplat128_64(lo)
			<= xft_vsplat128_64(hi - lo))));
}

#endif
