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
#include <xft/bmi.h>

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

__attribute__((__nonnull__(1, 4)))
static t_result	mem_writer_drain_fd(t_writer *w, t_fd fd, t_size limit,
	t_size *size)
{
	t_writer_ctx_memory *const	ctx = w->writer_ctx;
	const t_buffer				dst = ctx->buffer;
	t_reader_fs					fs;
	t_reader					r;
	t_size						n;

	n = 0;
	if (limit != 0 && dst.size != 0)
	{
		n = xft_tern_s(limit < dst.size, limit, dst.size);
		r = xft_fs_reader(&fs, fd, xft_fatptr(dst.mem, n));
		if (__builtin_expect(!xft_reader_read(&r, fs.buffer, &n), 0))
			return (KO);
	}
	ctx->buffer = xft_fatptr(dst.mem + n, dst.size - n);
	*size = n;
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
		.drain_fd = mem_writer_drain_fd,
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
