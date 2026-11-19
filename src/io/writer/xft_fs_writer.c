/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fs_writer.c                                    :+:      :+:    :+:   */
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
static t_result	xft__fs_writer_drain_all(t_writer *w, t_buffer data)
{
	t_writer_fs *const				ctx = w->writer_ctx;
	const t_buffer_with_capacity	buf = ctx->buffer;
	t_iovec							iov[2];
	t_result						ret;

	if (buf.mem == nullptr || data.mem == nullptr)
		__builtin_unreachable();
	if (data.size <= buf.capacity - buf.size)
	{
		xft_memcpy(buf.mem + buf.size, data.mem, data.size);
		ctx->buffer.size = buf.size + data.size;
		return ((t_result){.ok = OK});
	}
	iov[0] = (t_iovec){.mem = buf.mem, .size = buf.size};
	iov[1] = (t_iovec){.mem = data.mem, .size = data.size};
	ret = xft__fs_writer_writev(ctx, iov, 2);
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	ctx->buffer.size = 0;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_writer	xft_fs_writer(t_writer_fs *ctx, t_fd fd, t_buffer buffer)
{
	static t_writer_vtable const	vtable = {
		.drain_all = xft__fs_writer_drain_all,
		.drain_fd = xft__fs_writer_drain_fd,
		.flush = xft__fs_writer_flush,
	};

	if (buffer.mem == nullptr || buffer.size == 0)
		__builtin_unreachable();
	*ctx = (t_writer_fs){.fd = fd, .buffer = {.size = 0,
		.capacity = buffer.size, .mem = buffer.mem}};
	return ((t_writer){
		.writer_ctx = ctx,
		.vtable = vtable,
	});
}
