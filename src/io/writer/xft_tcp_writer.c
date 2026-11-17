/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tcp_writer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 18:28:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 18:30:39 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>
#include <xft/mem.h>

__attribute__((__nonnull__(1)))
static t_result	tcp_writer_drain_all(t_writer *w, t_buffer data)
{
	t_writer_ctx_tcp *const			ctx = w->writer_ctx;
	const t_buffer_with_capacity	buf = ctx->buf;
	t_iovec							iov[2];

	if (buf.mem == nullptr || data.mem == nullptr)
		__builtin_unreachable();
	if (data.size <= buf.capacity - buf.size)
	{
		xft_memcpy(buf.mem + buf.size, data.mem, data.size);
		ctx->buf.size = buf.size + data.size;
		return (OK);
	}
	iov[0] = (t_iovec){.mem = buf.mem, .size = buf.size};
	iov[1] = (t_iovec){.mem = data.mem, .size = data.size};
	if (__builtin_expect(!xft__tcp_writer_writev(ctx, iov, 2), 0))
		return (KO);
	ctx->buf.size = 0;
	return (OK);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_writer	xft_tcp_writer(t_writer_ctx_tcp *ctx,
	t_fd fd, t_buffer buffer)
{
	static t_writer_vtable const	vtable = {
		.drain_all = tcp_writer_drain_all,
		.drain_fd = xft__tcp_writer_drain_fd,
		.flush = xft__tcp_writer_flush,
	};

	if (buffer.mem == nullptr || buffer.size == 0)
		__builtin_unreachable();
	*ctx = (t_writer_ctx_tcp){.socket = fd, .buf = {.size = 0,
		.capacity = buffer.size, .mem = buffer.mem}};
	return ((t_writer){
		.writer_ctx = ctx,
		.vtable = vtable,
	});
}
