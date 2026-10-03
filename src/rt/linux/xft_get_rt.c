/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_rt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:38:36 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_rt.h"

#if defined(__linux__)

__attribute__((__nonnull__(1), __hot__, __always_inline__, __used__))
inline t_xft_rt	xft_get_rt(const t_any *sp)
{
	t_xft_rt	rt;

	rt.kp = xft_get_kernel_ptrs(sp);
	return (rt);
}

#endif
