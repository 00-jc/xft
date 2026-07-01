/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stfence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include <stdatomic.h>

#if defined(__x86_64__) || defined(_M_X64)

__attribute__((__always_inline__))
inline void	ft_stfence(void)
{
	__asm__("sfence" ::: "memory");
}

#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L \
	&& !defined(__STDC_NO_ATOMICS__)

__attribute__((__always_inline__))
inline void	ft_stfence(void)
{
	atomic_thread_fence(memory_order_seq_cst);
}

#else

__attribute__((__always_inline__))
inline void	ft_stfence(void)
{
	__sync_synchronize();
}

#endif
