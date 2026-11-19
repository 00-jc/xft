/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_map_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>

#if defined(__linux__)

# include <xft/xft_p_syscalls.h>

__attribute__((__nonnull__(1)))
t_buffer	xft_map_file_into_memory(const char *name)
{
	t_statx			st;
	int				fd;
	t_any			ptr;
	t_result		ret;

	fd = -1;
	ret = (t_result){.err = xft_err_retry};
	while (xft_should_retry(ret))
		ret = xft_open(name, xft_o_rdonly, 0, &fd);
	if (__builtin_expect(!ret.ok, 0))
		return ((t_buffer){0});
	ret = (t_result){.err = xft_err_retry};
	while (xft_should_retry(ret))
		ret = xft_fstatx(fd, xft_statx_size, &st);
	if (__builtin_expect(!ret.ok, 0))
		return ((void)xft_close(fd), (t_buffer){0});
	ptr = xft_fmap((t_size)st.stx_size, xft_prot_read, xft_map_private, fd);
	xft_close(fd);
	if (__builtin_expect(xft_map_failed(ptr).ok, 0))
		return ((t_buffer){0});
	return ((t_buffer){.size = (t_size)st.stx_size, .mem = ptr});
}

void	xft_unmap_file_from_memory(t_buffer buffer)
{
	if (buffer.mem == nullptr)
		__builtin_unreachable();
	xft_munmap(buffer.mem, buffer.size);
}

#endif
