/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fs_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 02:41:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_io.h>

#if defined(__linux__)

# include <xft/bmi.h>
# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1, 3)))
t_result	xft__fs_reader_discard(t_reader *r, t_size limit, t_size *size)
{
	const t_reader_fs	ctx = *(t_reader_fs *)r->reader_ctx;
	t_size				left;
	t_size				n;
	t_xft_sysres		ret;

	if (ctx.buffer.mem == nullptr)
		__builtin_unreachable();
	left = limit;
	n = 0;
	ret = xft_sys_repeat;
	while (left != 0 && (ret == xft_sys_repeat || n != 0))
	{
		ret = xft_read((int)ctx.fd, ctx.buffer.mem,
				xft_tern_s(left < ctx.buffer.size, left, ctx.buffer.size), &n);
		if (__builtin_expect(ret == xft_sys_ko, 0))
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
	t_size				n;
	t_xft_sysres		ret;

	if (dst.mem == nullptr)
		__builtin_unreachable();
	n = 0;
	ret = xft_sys_repeat;
	while (ret == xft_sys_repeat)
		ret = xft_read((int)ctx.fd, dst.mem, dst.size, &n);
	if (__builtin_expect(ret == xft_sys_ko, 0))
		return (KO);
	*size = n;
	return (OK);
}

__attribute__((__nonnull__(1)))
t_result	xft__fs_reader_read_all(t_reader *r, t_buffer dst)
{
	const t_reader_fs	ctx = *(t_reader_fs *)r->reader_ctx;
	t_size				done;
	t_size				n;
	t_xft_sysres		ret;

	if (dst.mem == nullptr)
		__builtin_unreachable();
	done = 0;
	while (done != dst.size)
	{
		ret = xft_read((int)ctx.fd, dst.mem + done, dst.size - done, &n);
		if (__builtin_expect(ret != xft_sys_repeat && n == 0, 0))
			return (KO);
		done += n;
	}
	return (OK);
}

#endif
