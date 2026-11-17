/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_udp_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 22:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 22:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>
#include <xft/bmi.h>
#include <xft/mem.h>

__attribute__((__nonnull__(1, 2, 4)))
static t_result	xft__udp_reader_stream(t_reader *r, t_writer *w, t_size limit,
	t_size *size)
{
	t_reader_ctx_udp *const	ctx = r->reader_ctx;
	const t_buffer			buf = ctx->buf;
	t_size					n;

	if (w->vtable.drain_all == nullptr)
		__builtin_unreachable();
	n = xft_tern_s(limit < buf.size, limit, buf.size);
	if (__builtin_expect(!xft__udp_reader_read(r, xft_fatptr(buf.mem, n), &n),
			0))
		return (KO);
	if (__builtin_expect(!w->vtable.drain_all(w, xft_fatptr(buf.mem, n)), 0))
		return (KO);
	*size = n;
	return (OK);
}

__attribute__((__nonnull__(1), __flatten__, __always_inline__, __used__))
inline t_reader	xft_udp_reader(t_reader_ctx_udp *ctx, t_fd fd, t_buffer buffer)
{
	static t_reader_vtable const	vtable = {
		.stream = xft__udp_reader_stream,
		.discard = xft__udp_reader_discard,
		.stream_all = xft__reader_stream_all,
		.discard_all = xft__reader_discard_all,
		.read = xft__udp_reader_read,
		.read_all = xft__reader_read_all,
	};

	if (buffer.mem == nullptr || buffer.size == 0)
		__builtin_unreachable();
	*ctx = (t_reader_ctx_udp){.buf = buffer, .socket = fd};
	return ((t_reader){
		.reader_ctx = ctx,
		.vtable = vtable,
	});
}
