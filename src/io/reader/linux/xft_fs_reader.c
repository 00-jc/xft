/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fs_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 02:41:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>

#if defined(__linux__)

# include <xft/bmi.h>
# include <xft/mem.h>
# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1, 2, 4)))
t_result	xft__fs_reader_stream(t_reader *r, t_writer *w, t_size limit,
	t_size *size)
{
	t_reader_fs *const	ctx = r->reader_ctx;
	t_size				len;
	t_size				n;
	t_xft_sysres		ret;
	t_buffer			chunk;

	if (ctx->buffer.mem == nullptr || w->vtable.drain_all == nullptr)
		__builtin_unreachable();
	*size = 0;
	n = 0;
	ret = xft_sys_repeat;
	while (*size != limit && (ret == xft_sys_repeat || n != 0))
	{
		len = xft_tern_s(limit - *size < ctx->buffer.size, limit - *size,
				ctx->buffer.size);
		ret = xft_read((int)ctx->fd, ctx->buffer.mem, len, &n);
		if (__builtin_expect(ret == xft_sys_ko, 0))
			return (KO);
		chunk = xft_fatptr(ctx->buffer.mem, n);
		if (__builtin_expect(!w->vtable.drain_all(w, chunk), 0))
			return (KO);
		*size += n;
	}
	return (OK);
}

__attribute__((__nonnull__(1, 3)))
t_result	xft__fs_reader_discard(t_reader *r, t_size limit, t_size *size)
{
	t_reader_fs *const	ctx = r->reader_ctx;
	t_size				len;
	t_size				n;
	t_xft_sysres		ret;

	if (ctx->buffer.mem == nullptr)
		__builtin_unreachable();
	*size = 0;
	n = 0;
	ret = xft_sys_repeat;
	while (*size != limit && (ret == xft_sys_repeat || n != 0))
	{
		len = xft_tern_s(limit - *size < ctx->buffer.size, limit - *size,
				ctx->buffer.size);
		ret = xft_read((int)ctx->fd, ctx->buffer.mem, len, &n);
		if (__builtin_expect(ret == xft_sys_ko, 0))
			return (KO);
		*size += n;
	}
	return (OK);
}

__attribute__((__nonnull__(1, 3)))
t_result	xft__fs_reader_read(t_reader *r, t_buffer dst, t_size *size)
{
	t_reader_fs *const	ctx = r->reader_ctx;
	t_size				len;
	t_size				n;
	t_xft_sysres		ret;

	if (dst.mem == nullptr)
		__builtin_unreachable();
	*size = 0;
	n = 0;
	ret = xft_sys_repeat;
	while (*size != dst.size && (ret == xft_sys_repeat || n != 0))
	{
		len = dst.size - *size;
		ret = xft_read((int)ctx->fd, dst.mem + *size, len, &n);
		if (__builtin_expect(ret == xft_sys_ko, 0))
			return (KO);
		*size += n;
	}
	return (OK);
}

#endif
