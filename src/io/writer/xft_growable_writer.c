/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_growable_writer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>
#include <xft/vec.h>
#include <xft/mem.h>
#include <xft/bmi.h>

__attribute__((__nonnull__(1)))
static t_result	xft__growable_writer_drain_all(t_writer *w, t_buffer data)
{
	t_writer_ctx_growable *const	ctx = w->writer_ctx;

	return (xft_vec_extend(ctx->allocator, &ctx->vec, data));
}

__attribute__((__nonnull__(1, 2, 4)))
static t_result	xft__growable_writer_drain_pipe(t_writer *w, t_reader *r,
	t_size limit, t_size *size)
{
	t_writer_ctx_growable *const	ctx = w->writer_ctx;
	t_buffer_with_capacity			buf;
	t_size							left;
	t_size							n;

	left = limit;
	n = 1;
	while (left != 0 && n != 0)
	{
		buf = ctx->vec.buf;
		n = xft_tern_s(left < buf.capacity, left, buf.capacity);
		if (__builtin_expect(buf.size == buf.capacity
				&& !xft_vec_reserve(ctx->allocator, &ctx->vec, n), 0))
			return (KO);
		buf = ctx->vec.buf;
		n = buf.capacity - buf.size;
		n = xft_tern_s(left < n, left, n);
		if (__builtin_expect(!xft_reader_read(r,
					xft_fatptr(buf.mem + buf.size, n), &n), 0))
			return (KO);
		ctx->vec.buf.size = buf.size + n;
		left -= n;
	}
	*size = limit - left;
	return (OK);
}

__attribute__((__nonnull__(1, 4)))
static t_result	xft__growable_writer_drain_fd(t_writer *w, t_fd fd,
	t_size limit, t_size *size)
{
	t_writer_ctx_growable *const	ctx = w->writer_ctx;
	const t_buffer_with_capacity	buf = ctx->vec.buf;
	t_file_info						info;
	t_reader_fs						fs;
	t_reader						r;

	if (__builtin_expect(!xft_fileinfo_from_fd(fd, &info), 0))
		return (KO);
	r = xft_fs_reader(&fs, fd, xft_fatptr(buf.mem, buf.capacity));
	if (info.size == 0)
		return (xft__growable_writer_drain_pipe(w, &r, limit, size));
	info.size = xft_tern_s(info.size < limit, (t_size)info.size, limit);
	if (__builtin_expect(!xft_vec_reserve(ctx->allocator, &ctx->vec,
				(t_size)info.size), 0))
		return (KO);
	if (__builtin_expect(!xft_reader_read_all(&r, xft_fatptr(ctx->vec.buf.mem
					+ buf.size, (t_size)info.size)), 0))
		return (KO);
	ctx->vec.buf.size = buf.size + (t_size)info.size;
	*size = (t_size)info.size;
	return (OK);
}

__attribute__((__nonnull__(1)))
static t_result	xft__growable_writer_flush(t_writer *w)
{
	(void)w;
	return (OK);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_writer	xft_growable_writer(t_writer_ctx_growable *ctx,
	t_allocator allocator, t_vec vec)
{
	static t_writer_vtable const	vtable = {
		.drain_all = xft__growable_writer_drain_all,
		.drain_fd = xft__growable_writer_drain_fd,
		.flush = xft__growable_writer_flush,
	};

	if (vec.buf.mem == nullptr)
		__builtin_unreachable();
	*ctx = (t_writer_ctx_growable){.allocator = allocator, .vec = vec};
	return ((t_writer){
		.writer_ctx = ctx,
		.vtable = vtable,
	});
}
