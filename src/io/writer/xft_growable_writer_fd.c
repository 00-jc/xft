/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_growable_writer_fd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>
#include <xft/vec.h>
#include <xft/mem.h>
#include <xft/bmi.h>

__attribute__((__nonnull__(1, 2, 4), __always_inline__))
static inline t_result	xft__growable_writer_step(
	t_writer_ctx_growable *ctx, t_reader *r, t_size left, t_size *n)
{
	t_buffer_with_capacity	buf;
	t_size					want;
	t_result				ret;

	buf = ctx->vec.buf;
	want = xft_tern_s(left < buf.capacity, left, buf.capacity);
	ret = (t_result){.ok = OK};
	if (__builtin_expect(buf.size == buf.capacity, 0))
		ret = xft_vec_reserve(ctx->allocator, &ctx->vec, want);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	buf = ctx->vec.buf;
	want = buf.capacity - buf.size;
	want = xft_tern_s(left < want, left, want);
	ret = xft_reader_read(r, xft_fatptr(buf.mem + buf.size, want), &want);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	ctx->vec.buf.size = buf.size + want;
	*n = want;
	return (ret);
}

__attribute__((__nonnull__(1, 2, 4)))
static t_result	xft__growable_writer_pipe_loop(t_writer *w, t_reader *r,
	t_size limit, t_size *size)
{
	t_writer_ctx_growable *const	ctx = w->writer_ctx;
	t_size							left;
	t_size							n;
	t_result						ret;

	left = limit;
	n = 1;
	while (left != 0 && n != 0)
	{
		ret = xft__growable_writer_step(ctx, r, left, &n);
		if (__builtin_expect(!ret.ok, 0))
			return (ret);
		left -= n;
	}
	*size = limit - left;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1, 4)))
static t_result	xft__growable_writer_drain_pipe(t_writer *w, t_fd fd,
	t_size limit, t_size *size)
{
	t_writer_ctx_growable *const	ctx = w->writer_ctx;
	const t_buffer_with_capacity	buf = ctx->vec.buf;
	t_reader_fs						fs;
	t_reader						r;

	r = xft_fs_reader(&fs, fd, xft_fatptr(buf.mem, buf.capacity));
	return (xft__growable_writer_pipe_loop(w, &r, limit, size));
}

__attribute__((__nonnull__(1, 4)))
static t_result	xft__growable_writer_drain_file(t_writer *w, t_fd fd,
	t_size n, t_size *size)
{
	t_writer_ctx_growable *const	ctx = w->writer_ctx;
	const t_buffer_with_capacity	buf = ctx->vec.buf;
	t_reader_fs						fs;
	t_reader						r;
	t_result						ret;

	r = xft_fs_reader(&fs, fd, xft_fatptr(buf.mem, buf.capacity));
	ret = xft_vec_reserve(ctx->allocator, &ctx->vec, n);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	ret = xft_reader_read_all(&r, xft_fatptr(ctx->vec.buf.mem + buf.size, n));
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	ctx->vec.buf.size = buf.size + n;
	*size = n;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1, 4)))
t_result	xft__growable_writer_drain_fd(t_writer *w, t_fd fd, t_size limit,
	t_size *size)
{
	t_file_info	info;
	t_result	ret;

	ret = xft_fileinfo_from_fd(fd, &info);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	if (info.size == 0)
		return (xft__growable_writer_drain_pipe(w, fd, limit, size));
	return (xft__growable_writer_drain_file(w, fd,
			xft_tern_s(info.size < limit, (t_size)info.size, limit), size));
}
