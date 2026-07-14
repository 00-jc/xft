/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_tls_variant_i.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"
#include "rt.h"
#include "private/ft_p_thread.h"

#if defined(TLS_VARIANT_I) || defined(TLS_VARIANT_I_MOD)

__attribute__((__always_inline__, unused, __nonnull__(1), pure))
inline t_size	ft__tcb_offset(const t_xft_rt *__restrict__ const rt_info)
{
	(void)rt_info;
	return (0);
}

__attribute__((__always_inline__, unused))
inline void	ft__write_abi_tcb(t_uptr tp)
{
	(void)tp;
}

__attribute__((__always_inline__, unused, __nonnull__(1), pure))
inline t_size	ft__block_offset(const t_xft_rt *__restrict__ const rt_info)
{
	return (ft_align_fwd_integer(sizeof(t_abi_tcb), rt_info->elf.align));
}

#endif
