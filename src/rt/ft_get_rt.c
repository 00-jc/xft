/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:38:36 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_rt.h"

#ifndef FT_NO_RT

__attribute__((__nonnull__(1), __hot__, __always_inline__))
inline t_xft_rt	ft_get_rt(const t_any *sp)
{
	t_xft_rt	rt;

	rt.kp = ft_get_kernel_ptrs(sp);
	ft_get_auxv_size(&rt, rt.kp.auxv);
	return (rt);
}

#endif
