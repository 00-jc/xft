/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_iota.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 19:43:11 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 19:59:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#ifdef XFT_HAS_512_VEC

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec	xft_viota(void)
{
	return (xft_viota512());
}

#elif defined(XFT_HAS_256_VEC)

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec	xft_viota(void)
{
	return (xft_viota256());
}

#elif defined(XFT_HAS_128_VEC)

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec	xft_viota(void)
{
	return (xft_viota128());
}

#else

__attribute__((__const__, __always_inline__, __used__))
inline t_nvec	xft_viota(void)
{
	return ((t_nvec){0, 1, 2, 3, 4, 5, 6, 7});
}

#endif
