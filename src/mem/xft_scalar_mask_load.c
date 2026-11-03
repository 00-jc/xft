/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_scalar_mask_load.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 13:41:34 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/03 17:09:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/mem.h>

__attribute__((__always_inline__, __hot__, __used__, __pure__, __nonnull__(3)))
inline t_u8	xft_mload_rel_u8(t_buffer mem, t_size rel, t_blk8r safe)
{
	t_cany		ptr;

	ptr = (t_cany)xft_tern(rel < mem.size,
			(t_uptr)mem.mem + rel, (t_uptr)safe);
	if (ptr == nullptr)
		__builtin_unreachable();
	return (*(t_blk8r)ptr);
}

__attribute__((__always_inline__, __hot__, __used__, __pure__, __nonnull__(3)))
inline t_u32	xft_mload_rel_u24(t_buffer mem, t_size rel, t_blk32r safe)
{
	t_cany		ptr;

	ptr = (t_cany)xft_tern(rel + 3 <= mem.size,
			(t_uptr)mem.mem + rel, (t_uptr)safe);
	if (ptr == nullptr)
		__builtin_unreachable();
	return (*(t_blk16r)ptr | (t_u32)((t_blk8r)ptr)[2] << 16);
}

__attribute__((__always_inline__, __hot__, __used__, __pure__, __nonnull__(3)))
inline t_u16	xft_mload_rel_u16(t_buffer mem, t_size rel, t_blk16r safe)
{
	t_cany		ptr;

	ptr = (t_cany)xft_tern(rel + 2 <= mem.size,
			(t_uptr)mem.mem + rel, (t_uptr)safe);
	if (ptr == nullptr)
		__builtin_unreachable();
	return (*(t_blk16r)ptr);
}

__attribute__((__always_inline__, __hot__, __used__, __pure__, __nonnull__(3)))
inline t_u32	xft_mload_rel_u32(t_buffer mem, t_size rel, t_blk32r safe)
{
	t_cany		ptr;

	ptr = (t_cany)xft_tern(rel + 4 <= mem.size,
			(t_uptr)mem.mem + rel, (t_uptr)safe);
	if (ptr == nullptr)
		__builtin_unreachable();
	return (*(t_blk32r)ptr);
}

__attribute__((__always_inline__, __hot__, __used__, __pure__, __nonnull__(3)))
inline t_u64	xft_mload_rel_u64(t_buffer mem, t_size rel, t_blk64r safe)
{
	t_cany		ptr;

	ptr = (t_cany)xft_tern(rel + 8 <= mem.size,
			(t_uptr)mem.mem + rel, (t_uptr)safe);
	if (ptr == nullptr)
		__builtin_unreachable();
	return (*(t_blk64r)ptr);
}
