/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fs_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>

#if defined(_WIN32)

# include <xft/bmi.h>
# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__nonnull__(1, 3)))
t_result	xft__fs_reader_discard(t_reader *r, t_size limit, t_size *size)
{
	const t_reader_fs	ctx = *(t_reader_fs *)r->reader_ctx;
	t_size				cap;
	t_size				left;
	DWORD				n;
	BOOL				ok;

	if (ctx.buffer.mem == nullptr)
		__builtin_unreachable();
	cap = xft_tern_s(ctx.buffer.size < MAXDWORD, ctx.buffer.size, MAXDWORD);
	left = limit;
	n = 1;
	while (left != 0 && n != 0)
	{
		ok = ReadFile((HANDLE)ctx.fd, ctx.buffer.mem,
				(DWORD)xft_tern_s(left < cap, left, cap), &n, nullptr);
		if (__builtin_expect(!ok && GetLastError() != ERROR_BROKEN_PIPE, 0))
			return (KO);
		left -= n;
	}
	*size = limit - left;
	return (OK);
}

__attribute__((__nonnull__(1, 3)))
t_result	xft__fs_reader_read(t_reader *r, t_buffer dst, t_size *size)
{
	const t_reader_fs	ctx = *(t_reader_fs *)r->reader_ctx;
	t_size				done;
	t_size				len;
	DWORD				n;
	BOOL				ok;

	if (dst.mem == nullptr)
		__builtin_unreachable();
	done = 0;
	n = 1;
	while (done != dst.size && n != 0)
	{
		len = dst.size - done;
		len = xft_tern_s(len < MAXDWORD, len, MAXDWORD);
		ok = ReadFile((HANDLE)ctx.fd, dst.mem + done, (DWORD)len, &n, nullptr);
		if (__builtin_expect(!ok && GetLastError() != ERROR_BROKEN_PIPE, 0))
			return (KO);
		done += n;
	}
	*size = done;
	return (OK);
}

#endif
