/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fences.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 20:36:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/03 20:36:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atomics.h"

__attribute__((__always_inline__))
inline void	ft_thread_fence(t_i32a memorder)
{
	__atomic_thread_fence(memorder);
}

__attribute__((__always_inline__))
inline void	ft_signal_fence(t_i32a memorder)
{
	__atomic_signal_fence(memorder);
}
