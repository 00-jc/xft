/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_kernel_ptrs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 11:41:36 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_rt.h"

#ifndef FT_NO_RT

__attribute__((__nonnull__(1), __hot__, __always_inline__))
inline t_kernel_ptrs	ft_get_kernel_ptrs(const t_any *__restrict__ const sp)
{
	t_kernel_ptrs	kp;
	t_auxv			auxv;

	kp.argc = ((const t_u64 *)sp)[0];
	kp.argv = (t_rt_arr)(sp + 1);
	kp.envp = kp.argv + kp.argc + 1;
	kp.envc = ft_get_envp_size(kp.envp);
	kp.auxv = (t_any)(kp.envp + kp.envc + 1);
	auxv = kp.auxv;
	kp.auxc = 0;
	while (auxv[kp.auxc].a_type != AT_NULL)
		++kp.auxc;
	return (kp);
}

#endif
