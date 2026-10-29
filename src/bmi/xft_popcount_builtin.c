/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_popcount_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:43:03 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 12:48:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>

#if __has_builtin(__builtin_popcountg)

__attribute__((__const__, __always_inline__, __used__))
inline t_u32a	xft_popcount_u32(t_u32a x)
{
	return ((t_u32a)__builtin_popcountg(x));
}

__attribute__((__const__, __always_inline__, __used__))
inline t_u64a	xft_popcount_u64(t_u64a x)
{
	return ((t_u64a)__builtin_popcountg(x));
}

#endif
