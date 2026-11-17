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

#if defined(__linux__)

# include <xft/bmi.h>
# include <xft/xft_p_net.h>
# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1)))
t_result	xft__udp_writer_send(t_writer_ctx_udp *ctx, t_buffer data)
{
	const int		fd = (int)ctx->socket;
	t_sockaddr_in6	sa;
	t_iovec			iov;
	t_xft_sysres	ret;

	xft__sockaddr_from_ip(&ctx->ip, &sa);
	iov = (t_iovec){.mem = data.mem};
	ret = xft_sys_repeat;
	while (ret == xft_sys_repeat)
	{
		iov.size = data.size;
		ret = xft_sendto(fd, &iov, (t_xft_msg_opts){0}, &sa);
	}
	return ((t_result)(ret == xft_sys_ok && iov.size == data.size));
}

__attribute__((__nonnull__(1, 4)))
t_result	xft__udp_writer_drain_fd(t_writer *w, t_fd fd, t_size limit,
	t_size *size)
{
	t_writer_ctx_udp *const	ctx = w->writer_ctx;
	const t_size			cap = ctx->buf.capacity;
	t_size					left;
	t_size					n;
	t_xft_sysres			ret;

	left = limit;
	n = 0;
	ret = xft_sys_repeat;
	while (left != 0 && (ret == xft_sys_repeat || n != 0))
	{
		if (__builtin_expect(!xft__udp_writer_flush(w), 0))
			return (KO);
		ret = xft_read((int)fd, ctx->buf.mem,
				xft_tern_s(left < cap, left, cap), &n);
		if (__builtin_expect(ret == xft_sys_ko, 0))
			return (KO);
		ctx->buf.size = n;
		left -= n;
	}
	*size = limit - left;
	return (OK);
}

#endif
