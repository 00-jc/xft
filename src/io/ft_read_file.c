/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 02:23:38 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/20 10:16:40 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

#ifdef __x86_64__

__attribute__((__nonnull__(2)))
t_file	ft_read_file(t_allocator alloc, const char *restrict const fname)
{
	int					ret;
	struct stat			st;
	void				*ptr;

	(void)alloc;
	ret = ft_stat(fname, &st);
	if (ret == -1)
		return ((t_file){0});
	ret = open(fname, O_RDONLY);
	if (ret == -1)
		return ((t_file){0});
	ft_lockf(ret);
	ptr = ft_fmap((size_t)st.st_size, ret);
	if (ptr == MAP_FAILED)
		return ((void)ft_unlockf(ret), (void)close(ret), (t_file){0});
	return ((t_file){.content = ptr,
		.size = (size_t)st.st_size, .fd = (t_u32a)ret});
}

__attribute__((__nonnull__(2)))
inline void	ft_close_file(t_allocator alloc, t_file *restrict const f)
{
	int	fd;

	(void)alloc;
	fd = (int)f->fd;
	(void)ft_unlockf(fd);
	ft_munmap(f->content, f->size);
	(void)close(fd);
}

#endif
