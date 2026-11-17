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

#if defined(_WIN32)

# include <xft/bmi.h>
# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>

__attribute__((__nonnull__(1, 3)))
t_result	xft__tcp_reader_discard(t_reader *r, t_size limit, t_size *size)
{
	const t_reader_ctx_tcp	ctx = *(t_reader_ctx_tcp *)r->reader_ctx;
	t_size					cap;
	t_size					left;
	int						n;

	cap = xft_tern_s(ctx.buf.size < MAXLONG, ctx.buf.size, MAXLONG);
	left = limit;
	n = 1;
	while (left != 0 && n != 0)
	{
		n = recv((SOCKET)ctx.socket, (char *)ctx.buf.mem,
				(int)xft_tern_s(left < cap, left, cap), 0);
		if (__builtin_expect(n < 0, 0))
			return (KO);
		left -= (t_size)n;
	}
	*size = limit - left;
	return (OK);
}

__attribute__((__nonnull__(1, 3)))
t_result	xft__tcp_reader_read(t_reader *r, t_buffer dst, t_size *size)
{
	const t_reader_ctx_tcp	ctx = *(t_reader_ctx_tcp *)r->reader_ctx;
	t_size					done;
	t_size					len;
	int						n;

	if (dst.mem == nullptr)
		__builtin_unreachable();
	done = 0;
	n = 1;
	while (done != dst.size && n != 0)
	{
		len = dst.size - done;
		len = xft_tern_s(len < MAXLONG, len, MAXLONG);
		n = recv((SOCKET)ctx.socket, (char *)dst.mem + done, (int)len,
				MSG_WAITALL);
		if (__builtin_expect(n < 0, 0))
			return (KO);
		done += (t_size)n;
	}
	*size = done;
	return (OK);
}

#endif
