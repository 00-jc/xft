/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_cache_line_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 22:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/28 22:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_rt.h>

#if !defined(__x86_64__) && !defined(__i386__) && !defined(__aarch64__)

__attribute__((const, __always_inline__, __used__))
inline t_u32a	xft_cache_line_size(void)
{
	return (__GCC_CONSTRUCTIVE_SIZE);
}

#endif
