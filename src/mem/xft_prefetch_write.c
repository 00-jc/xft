/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_prefetch_write.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/mem.h>

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_prefetch_write0(t_cany restrict const ptr,
	t_size distance)
{
	__builtin_prefetch((const t_u8 *)ptr + distance, 1, 3);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_prefetch_write1(t_cany restrict const ptr,
	t_size distance)
{
	__builtin_prefetch((const t_u8 *)ptr + distance, 1, 2);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_prefetch_write2(t_cany restrict const ptr,
	t_size distance)
{
	__builtin_prefetch((const t_u8 *)ptr + distance, 1, 1);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_prefetch_writenta(t_cany restrict const ptr,
	t_size distance)
{
	__builtin_prefetch((const t_u8 *)ptr + distance, 1, 0);
}
