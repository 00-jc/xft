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
static t_result	xft__mem_reader_stream(t_reader *r, t_writer *w, t_size limit,
	t_size *size)
{
	t_reader_ctx_memory *const	ctx = r->reader_ctx;
	const t_buffer				src = ctx->buffer;
	t_size						n;
	t_result					ret;

	if (w->vtable.drain_all == nullptr)
		__builtin_unreachable();
	n = xft_tern_s(limit < src.size, limit, src.size);
	ret = w->vtable.drain_all(w, xft_fatptr(src.mem, n));
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	ctx->buffer = xft_fatptr(src.mem + n, src.size - n);
	*size = n;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1, 3)))
static t_result	xft__mem_reader_discard(t_reader *r, t_size limit, t_size *size)
{
	t_reader_ctx_memory *const	ctx = r->reader_ctx;
	const t_buffer				src = ctx->buffer;
	t_size						n;

	n = xft_tern_s(limit < src.size, limit, src.size);
	ctx->buffer = xft_fatptr(src.mem + n, src.size - n);
	*size = n;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1, 3)))
static t_result	xft__mem_reader_read(t_reader *r, t_buffer dst, t_size *size)
{
	t_reader_ctx_memory *const	ctx = r->reader_ctx;
	const t_buffer				src = ctx->buffer;
	t_size						n;

	n = xft_tern_s(dst.size < src.size, dst.size, src.size);
	xft_memcpy(dst.mem, src.mem, n);
	ctx->buffer = xft_fatptr(src.mem + n, src.size - n);
	*size = n;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_reader	xft_mem_reader(t_reader_ctx_memory *ctx, t_buffer src)
{
	static t_reader_vtable const	vtable = {
		.stream = xft__mem_reader_stream,
		.discard = xft__mem_reader_discard,
		.stream_all = xft__reader_stream_all,
		.discard_all = xft__reader_discard_all,
		.read = xft__mem_reader_read,
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
