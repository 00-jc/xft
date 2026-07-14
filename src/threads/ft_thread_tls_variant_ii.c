/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_tls_variant_ii.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "private/ft_p_thread.h"

#if defined(TLS_VARIANT_II)

__attribute__((__always_inline__, unused, __nonnull__(1), pure))
inline t_size	ft__tcb_offset(const t_xft_rt *__restrict__ const rt_info)
{
	return (rt_info->elf.memsz);
}

__attribute__((__always_inline__, unused, __nonnull__(1), pure))
inline t_size	ft__block_offset(const t_xft_rt *__restrict__ const rt_info)
{
	(void)rt_info;
	return (0);
}

__attribute__((__always_inline__, unused))
inline void	ft__write_abi_tcb(t_abi_tcb *__restrict__ const tp)
{
	((t_abi_tcb *)tp)->self = tp;
}

#endif
