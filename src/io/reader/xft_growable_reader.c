/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_growable_reader.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 02:43:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>
#include <xft/bmi.h>
#include <xft/mem.h>

__attribute__((__nonnull__(1, 2, 4)))
static t_result	growable_reader_stream(t_reader *r, t_writer *w, t_size limit,
	t_size *size)
{
	t_reader_ctx_growable *const	ctx = r->reader_ctx;
	t_size							hoist;
	t_buffer						chunk;

	if (ctx->vec.buf.mem == nullptr || w->vtable.drain_all == nullptr)
		__builtin_unreachable();
	hoist = xft_tern_s(limit < ctx->vec.buf.size, limit, ctx->vec.buf.size);
	chunk = xft_fatptr(ctx->vec.buf.mem, hoist);
	if (__builtin_expect(!w->vtable.drain_all(w, chunk), 0))
		return (KO);
	ctx->vec.buf.size -= hoist;
	xft_memmove(ctx->vec.buf.mem, ctx->vec.buf.mem + hoist, ctx->vec.buf.size);
	*size = hoist;
	return (OK);
}

__attribute__((__nonnull__(1, 3)))
static t_result	growable_reader_discard(t_reader *r, t_size limit,
	t_size *size)
{
	t_reader_ctx_growable *const	ctx = r->reader_ctx;
	t_size							hoist;

	if (ctx->vec.buf.mem == nullptr)
		__builtin_unreachable();
	hoist = xft_tern_s(limit < ctx->vec.buf.size, limit, ctx->vec.buf.size);
	ctx->vec.buf.size -= hoist;
	xft_memmove(ctx->vec.buf.mem, ctx->vec.buf.mem + hoist, ctx->vec.buf.size);
	*size = hoist;
	return (OK);
}

__attribute__((__nonnull__(1, 3)))
static t_result	growable_reader_read(t_reader *r, t_buffer dst, t_size *size)
{
	t_reader_ctx_growable *const	ctx = r->reader_ctx;

	if (ctx->vec.buf.mem == nullptr)
		__builtin_unreachable();
	*size = xft_tern_s(dst.size < ctx->vec.buf.size, dst.size,
			ctx->vec.buf.size);
	xft_memcpy(dst.mem, ctx->vec.buf.mem, *size);
	ctx->vec.buf.size -= *size;
	xft_memmove(ctx->vec.buf.mem, ctx->vec.buf.mem + *size, ctx->vec.buf.size);
	return (OK);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_reader	xft_growable_reader(t_reader_ctx_growable *ctx, t_vec vec)
{
	static t_reader_vtable const	vtable = {
		.stream = growable_reader_stream,
		.discard = growable_reader_discard,
		.stream_all = xft__reader_stream_all,
		.discard_all = xft__reader_discard_all,
		.read = growable_reader_read,
		.read_all = xft__reader_read_all,
	};

	if (vec.buf.mem == nullptr)
		__builtin_unreachable();
	*ctx = (t_reader_ctx_growable){.vec = vec};
	return ((t_reader){
		.reader_ctx = ctx,
		.vtable = vtable,
	});
}
