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

#if defined(__linux__)

# include <xft/bmi.h>
# include <xft/xft_p_net.h>
# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1, 3)))
t_result	xft__udp_reader_discard(t_reader *r, t_size limit, t_size *size)
{
	t_reader_ctx_udp *const	ctx = r->reader_ctx;
	t_sockaddr_in6			sa;
	t_iovec					iov;
	t_result				ret;

	iov = (t_iovec){.mem = ctx->buf.mem};
	ret = (t_result){.err = xft_err_retry};
	while (xft_should_retry(ret))
	{
		iov.size = 0;
		ret = xft_recvfrom((int)ctx->socket, &iov,
				(t_xft_msg_opts){.trunc = 1}, &sa);
	}
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	xft__ip_from_sockaddr(&sa, &ctx->ip);
	*size = xft_tern_s(iov.size < limit, iov.size, limit);
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(1, 3)))
t_result	xft__udp_reader_read(t_reader *r, t_buffer dst, t_size *size)
{
	t_reader_ctx_udp *const	ctx = r->reader_ctx;
	t_sockaddr_in6			sa;
	t_iovec					iov;
	t_result				ret;

	if (dst.mem == nullptr)
		__builtin_unreachable();
	iov = (t_iovec){.mem = dst.mem};
	ret = (t_result){.err = xft_err_retry};
	while (xft_should_retry(ret))
	{
		iov.size = dst.size;
		ret = xft_recvfrom((int)ctx->socket, &iov, (t_xft_msg_opts){0}, &sa);
	}
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	xft__ip_from_sockaddr(&sa, &ctx->ip);
	*size = iov.size;
	return ((t_result){.ok = OK});
}

#endif
