/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 02:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/18 02:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft.h>

static t_u8	g_rbuf[4096];
static t_u8	g_wbuf[65536];

static t_result	cat_file(t_writer *out, const t_u8 *path)
{
	const t_fileopen_mode	mode = {.read = 1};
	t_reader_fs				rctx;
	t_reader				r;
	t_fd					fd;
	t_size					n;

	if (!xft_open_file(path, mode, &fd))
		return (KO);
	r = xft_fs_reader(&rctx, fd, xft_fatptr(g_rbuf, sizeof(g_rbuf)));
	if (!xft_reader_stream(&r, out, (t_size)-1, &n))
	{
		(void)xft_close_file(fd);
		return (KO);
	}
	return (xft_close_file(fd));
}

void	xft_main(const t_any *__restrict__ const sp)
{
	t_kernel_ptrs	kp;
	t_writer_fs		wctx;
	t_writer		w;
	t_size			i;
	t_i32a			status;

	kp = xft_get_kernel_ptrs(sp);
	w = xft_fs_writer(&wctx, xft_get_stdout(),
			xft_fatptr(g_wbuf, sizeof(g_wbuf)));
	status = 0;
	i = 1;
	while (i < kp.argc)
	{
		if (!cat_file(&w, kp.argv[i]))
			status = 1;
		++i;
	}
	if (!xft_writer_flush(&w))
		status = 1;
	xft_kernel_ptrs_destroy(&kp);
	xft_exit_process(status);
}
