/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memfence.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 00:19:38 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 01:25:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include <stdatomic.h>

#if defined(__x86_64__) || defined(_M_X64)

__attribute__((__always_inline__))
inline void	ft_fence(void)
{
	__asm__("sfence" ::: "memory");
}

#elif defined(__aarch64__) || defined(_M_ARM64)

__attribute__((__always_inline__))
inline void	ft_fence(void)
{
	__asm__ ("dsb st" ::: "memory");
}

#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L \
	&& !defined(__STDC_NO_ATOMICS__)

__attribute__((__always_inline__))
inline void	ft_fence(void)
{
	atomic_thread_fence(memory_order_seq_cst);
}

#else

__attribute__((__always_inline__))
inline void	ft_fence(void)
{
	__sync_synchronize();
}

#endif
