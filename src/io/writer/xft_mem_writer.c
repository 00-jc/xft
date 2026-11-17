/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mem_writer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>
#include <xft/mem.h>

__attribute__((__nonnull__(1)))
static t_result	mem_writer_drain_all(t_writer *w, t_buffer data)
{
	t_writer_ctx_memory *const	ctx = w->writer_ctx;

	if (__builtin_expect(data.size > ctx->buffer.size, 0))
		return (KO);
	xft_memcpy(ctx->buffer.mem, data.mem, data.size);
	ctx->buffer.mem += data.size;
	ctx->buffer.size -= data.size;
	return (OK);
}

__attribute__((__nonnull__(1)))
static t_result	mem_writer_flush(t_writer *w)
{
	(void)w;
	return (OK);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_writer	xft_mem_writer(t_writer_ctx_memory *ctx, t_buffer dst)
{
	static t_writer_vtable const	vtable = {
		.drain_all = mem_writer_drain_all,
		.flush = mem_writer_flush,
	};

	if (dst.mem == nullptr)
		__builtin_unreachable();
	*ctx = (t_writer_ctx_memory){.buffer = dst};
	return ((t_writer){
		.writer_ctx = ctx,
		.vtable = vtable,
	});
}
