/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_align.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 17:51:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/02 20:14:39 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"

__attribute__((const, __always_inline__, __used__))
inline t_u64a	xft_align_fwd_integer(t_u64a qw, const t_u64a align)
{
	return (((qw + align - 1) & ~(align - 1)));
}

__attribute__((const, __always_inline__, __used__))
inline t_u64a	xft_align_bwd_integer(t_u64a qw, const t_u64a align)
{
	return ((qw & ~(align - 1)));
}
