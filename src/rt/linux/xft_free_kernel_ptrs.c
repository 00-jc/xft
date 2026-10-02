/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_free_kernel_ptrs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 20:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 20:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(__linux__)

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_free_kernel_ptrs(t_kernel_ptrs *kp)
{
	(void)kp;
}

#endif
