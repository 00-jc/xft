/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_udp_writer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 22:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 22:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>
#include <xft/mem.h>

__attribute__((__nonnull__(1)))
t_result	xft__udp_writer_flush(t_writer *w)
{
	t_writer_ctx_udp *const			ctx = w->writer_ctx;
	const t_buffer_with_capacity	buf = ctx->buf;

	if (buf.size == 0)
		return (OK);
	if (__builtin_expect(!xft__udp_writer_send(ctx,
				xft_fatptr(buf.mem, buf.size)), 0))
		return (KO);
	ctx->buf.size = 0;
	return (OK);
}

__attribute__((__nonnull__(1)))
static t_result	udp_writer_drain_all(t_writer *w, t_buffer data)
{
	t_writer_ctx_udp *const			ctx = w->writer_ctx;
	const t_buffer_with_capacity	buf = ctx->buf;

	if (buf.mem == nullptr || data.mem == nullptr)
		__builtin_unreachable();
	if (data.size <= buf.capacity - buf.size)
	{
		xft_memcpy(buf.mem + buf.size, data.mem, data.size);
		ctx->buf.size = buf.size + data.size;
		return (OK);
	}
	if (__builtin_expect(!xft__udp_writer_flush(w), 0))
		return (KO);
	if (data.size > buf.capacity)
		return (xft__udp_writer_send(ctx, data));
	xft_memcpy(buf.mem, data.mem, data.size);
	ctx->buf.size = data.size;
	return (OK);
}

__attribute__((__nonnull__(1, 4), __flatten__, __always_inline__, __used__))
inline t_writer	xft_udp_writer(t_writer_ctx_udp *ctx, t_fd fd,
	t_buffer buffer, const t_ip_addr *dest)
{
	static t_writer_vtable const	vtable = {
		.drain_all = udp_writer_drain_all,
		.drain_fd = xft__udp_writer_drain_fd,
		.flush = xft__udp_writer_flush,
	};

	if (buffer.mem == nullptr || buffer.size == 0)
		__builtin_unreachable();
	*ctx = (t_writer_ctx_udp){.socket = fd, .ip = *dest, .buf = {.size = 0,
		.capacity = buffer.size, .mem = buffer.mem}};
	return ((t_writer){
		.writer_ctx = ctx,
		.vtable = vtable,
	});
}
