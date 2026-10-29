/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fences.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 20:36:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/03 20:36:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/atomics.h>
#include <stdatomic.h>

__attribute__((__always_inline__, __used__))
inline void	xft_thread_fence(t_xft_atomic_ordering memorder)
{
	atomic_thread_fence(memorder);
}

__attribute__((__always_inline__, __used__))
inline void	xft_signal_fence(t_xft_atomic_ordering memorder)
{
	atomic_signal_fence(memorder);
}
