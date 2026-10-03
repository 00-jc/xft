/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_kernel_ptrs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 14:02:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_rt.h"

#if defined(__linux__)

__attribute__((__nonnull__(1), __hot__, __always_inline__, __used__))
inline t_kernel_ptrs	xft_get_kernel_ptrs(const t_any *__restrict__ const sp)
{
	t_kernel_ptrs	kp;

	kp.argc = ((const t_u64 *)sp)[0];
	kp.argv = (t_rt_arr)(sp + 1);
	kp.envp = kp.argv + kp.argc + 1;
	return (kp);
}

#endif
