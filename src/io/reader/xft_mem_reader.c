/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mem_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>
#include <xft/bmi.h>
#include <xft/mem.h>

__attribute__((__nonnull__(1, 2, 4)))
static t_result	mem_reader_stream(t_reader *r, t_writer *w, t_size limit,
	t_size *size)
{
	t_reader_ctx_memory *const	ctx = r->reader_ctx;
	t_buffer					chunk;

	if (w->vtable.drain_all == nullptr)
		__builtin_unreachable();
	*size = xft_tern_s(limit < ctx->buffer.size, limit, ctx->buffer.size);
	chunk = xft_fatptr(ctx->buffer.mem, *size);
	if (__builtin_expect(!w->vtable.drain_all(w, chunk), 0))
		return (KO);
	ctx->buffer.mem += *size;
	ctx->buffer.size -= *size;
	return (OK);
}

__attribute__((__nonnull__(1, 3)))
static t_result	mem_reader_discard(t_reader *r, t_size limit, t_size *size)
{
	t_reader_ctx_memory *const	ctx = r->reader_ctx;

	*size = xft_tern_s(limit < ctx->buffer.size, limit, ctx->buffer.size);
	ctx->buffer.mem += *size;
	ctx->buffer.size -= *size;
	return (OK);
}

__attribute__((__nonnull__(1, 3)))
static t_result	mem_reader_read(t_reader *r, t_buffer dst, t_size *size)
{
	t_reader_ctx_memory *const	ctx = r->reader_ctx;

	*size = xft_tern_s(dst.size < ctx->buffer.size, dst.size, ctx->buffer.size);
	xft_memcpy(dst.mem, ctx->buffer.mem, *size);
	ctx->buffer.mem += *size;
	ctx->buffer.size -= *size;
	return (OK);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_reader	xft_mem_reader(t_reader_ctx_memory *ctx, t_buffer src)
{
	static t_reader_vtable const	vtable = {
		.stream = mem_reader_stream,
		.discard = mem_reader_discard,
		.stream_all = xft__reader_stream_all,
		.discard_all = xft__reader_discard_all,
		.read = mem_reader_read,
		.read_all = xft__reader_read_all,
	};

	if (src.mem == nullptr)
		__builtin_unreachable();
	*ctx = (t_reader_ctx_memory){.buffer = src};
	return ((t_reader){
		.reader_ctx = ctx,
		.vtable = vtable,
	});
}
