/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_open_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 22:42:03 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/27 22:42:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/files.h>

#if defined(__linux__)

# include <xft/xft_p_syscalls.h>

__attribute__((__always_inline__, __const__))
static inline int	xft__open_flags(t_fileopen_mode mode)
{
	int	flags;

	flags = xft_o_rdonly;
	if (mode.read && (mode.write || mode.append))
		flags = xft_o_rdwr;
	else if (mode.write || mode.append)
		flags = xft_o_wronly;
	if (mode.create || mode.exclusive)
		flags |= xft_o_creat;
	if (mode.exclusive)
		flags |= xft_o_excl;
	if (mode.truncate)
		flags |= xft_o_trunc;
	if (mode.append)
		flags |= xft_o_append;
	return (flags);
}

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_fd	xft_open_file(t_blk8r path, t_fileopen_mode mode)
{
	return ((t_fd)xft_open((const char *)path, xft__open_flags(mode),
			xft_open_0666));
}

__attribute__((__always_inline__, __used__))
inline t_fd	xft_close_file(t_fd fd)
{
	return ((t_fd)xft_close((int)fd));
}

#endif
