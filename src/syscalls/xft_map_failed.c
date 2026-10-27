/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_map_failed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 02:41:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 02:41:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/syscalls.h>

#if defined(__linux__)

# include <xft/xft_p_syscalls.h>

__attribute__((const, __hot__, __always_inline__, __used__))
inline t_result	xft_map_failed(t_cany ptr)
{
	return ((t_uptr)ptr >= (t_uptr)-xft_max_errno);
}

#endif
