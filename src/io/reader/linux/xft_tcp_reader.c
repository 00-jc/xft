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

#if defined(__linux__)

# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1, 3)))
t_result	xft__tcp_reader_discard(t_reader *r, t_size limit, t_size *size)
{
	const t_reader_ctx_tcp	ctx = *(t_reader_ctx_tcp *)r->reader_ctx;
	t_size					left;
	t_iovec					iov;
	t_xft_sysres			ret;

	left = limit;
	iov = (t_iovec){.mem = ctx.buf.mem};
	ret = xft_sys_repeat;
	while (left != 0 && (ret == xft_sys_repeat || iov.size != 0))
	{
		iov = (t_iovec){.mem = ctx.buf.mem, .size = left};
		ret = xft_recvfrom((int)ctx.socket, &iov,
				(t_xft_msg_opts){.trunc = 1}, nullptr);
		if (__builtin_expect(ret == xft_sys_ko, 0))
			return (KO);
		left -= iov.size;
	}
	*size = limit - left;
	return (OK);
}

__attribute__((__nonnull__(1, 3)))
t_result	xft__tcp_reader_read(t_reader *r, t_buffer dst, t_size *size)
{
	const t_reader_ctx_tcp	ctx = *(t_reader_ctx_tcp *)r->reader_ctx;
	t_size					done;
	t_iovec					iov;
	t_xft_sysres			ret;

	if (dst.mem == nullptr)
		__builtin_unreachable();
	done = 0;
	iov = (t_iovec){.mem = dst.mem};
	ret = xft_sys_repeat;
	while (done != dst.size && (ret == xft_sys_repeat || iov.size != 0))
	{
		iov = (t_iovec){.mem = dst.mem + done, .size = dst.size - done};
		ret = xft_recvfrom((int)ctx.socket, &iov,
				(t_xft_msg_opts){.waitall = 1}, nullptr);
		if (__builtin_expect(ret == xft_sys_ko, 0))
			return (KO);
		done += iov.size;
	}
	*size = done;
	return (OK);
}

#endif
