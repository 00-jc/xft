/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_example.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 20:42:45 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/12 21:06:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft.h"

__attribute__((__nonnull__(1)))
void	xft_main(const t_any *__restrict__ const sp)
{
	t_kernel_ptrs	kp;

	kp = xft_get_kernel_ptrs(sp);
	__asm__("":: "m"(kp) :"memory");
	xft_kernel_ptrs_destroy(&kp);
	xft_exit(0);
}
