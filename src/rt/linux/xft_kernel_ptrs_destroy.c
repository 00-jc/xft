/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_kernel_ptrs_destroy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 20:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 20:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/rt.h>

#if defined(__linux__)

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_kernel_ptrs_destroy(t_kernel_ptrs *kp)
{
	(void)kp;
}

#endif
