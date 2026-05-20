/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file_portable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 03:52:23 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/20 10:20:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "vec.h"

#ifndef __x86_64__

__attribute__((__nonnull__(2)))
t_file	ft_read_file(t_allocator alloc, const char *restrict const fname)
{
	ssize_t		ret;
	int			fd;
	t_vec		buffer;

	buffer = ft_vec(alloc, BUFSIZE, sizeof(t_u8));
	if (buffer.buf.mem == nullptr)
		return ((t_file){0});
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (ft_vec_destroy(alloc, &buffer), (t_file){0});
	ret = ft_read(fd, buffer.buf.mem, BUFSIZE);
	while (ret > 0)
	{
		buffer.size += ret;
		if (!ft_vec_reserve(alloc, &buffer, sizeof(t_u8), BUFSIZE))
			return (ft_vec_destroy(alloc, &buffer),
				(void)close(fd), (t_file){0});
		ret = ft_read(fd, (t_u8 *)buffer.buf.mem + buffer.size, BUFSIZE);
	}
	if (ret < 0)
		return (ft_vec_destroy(alloc, &buffer),
			(void)close(fd), (t_file){0});
	return ((t_file){.content = (t_u8 *)buffer.buf.mem,
		.size = (t_uptr)buffer.size,
		.fd = (t_u32)fd});
}

__attribute__((__nonnull__(2)))
inline void	ft_close_file(t_allocator alloc, t_file *restrict const f)
{
	(void)close((int)f->fd);
	alloc.interface.free(alloc.allocator,
		(t_buffer){.mem = f->content, .size = f->size});
}

#endif
