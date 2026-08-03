/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 09:06:33 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 23:14:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

__attribute__((__always_inline__, __nonnull__(1)))
inline t_buffer	ft_map_file(const t_u8 *__restrict__ const name, t_u32 flags)
{
	t_i32	fd;
	t_stat	stat;
	t_any	ptr;

	if (__builtin_expect(ft_stat((t_any)name, &stat), 0))
		return ((t_buffer){0});
	fd = ft_open((t_any)name, flags);
	if (__builtin_expect(fd == -1, 0))
		return ((t_buffer){0});
	ptr = ft_fmap(stat.st_size, fd);
	if (__builtin_expect(ft_map_failed(ptr), 0))
		return ((void)ft_close(fd), (t_buffer){0});
	ft_close(fd);
	return ((t_buffer){.size = stat.st_size, .mem = ptr});
}

__attribute__((__always_inline__))
inline void	ft_unmap_file(t_buffer file)
{
	ft_munmap(file.mem, file.size);
}
