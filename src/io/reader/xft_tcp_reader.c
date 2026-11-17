/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tcp_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>

__attribute__((__nonnull__(1, 2, 4)))
static t_result	xft__tcp_reader_stream(t_reader *r, t_writer *w, t_size limit,
	t_size *size)
{
	t_reader_ctx_tcp *const	ctx = r->reader_ctx;

	if (w->vtable.drain_fd == nullptr)
		__builtin_unreachable();
	return (w->vtable.drain_fd(w, ctx->socket, limit, size));
}

__attribute__((__nonnull__(1), __flatten__, __always_inline__, __used__))
inline t_reader	xft_tcp_reader(t_reader_ctx_tcp *ctx, t_fd fd, t_buffer buffer)
{
	static t_reader_vtable const	vtable = {
		.stream = xft__tcp_reader_stream,
		.discard = xft__tcp_reader_discard,
		.stream_all = xft__reader_stream_all,
		.discard_all = xft__reader_discard_all,
		.read = xft__tcp_reader_read,
		.read_all = xft__tcp_reader_read_all,
	};

	if (buffer.mem == nullptr || buffer.size == 0)
		__builtin_unreachable();
	*ctx = (t_reader_ctx_tcp){.buf = buffer, .socket = fd};
	return ((t_reader){
		.reader_ctx = ctx,
		.vtable = vtable,
	});
}
