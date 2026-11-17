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

# include <xft/bmi.h>
# include <xft/xft_p_syscalls.h>

__attribute__((__always_inline__, __const__))
static inline int	xft__open_flags(t_fileopen_mode mode)
{
	const bool	writes = mode.write || mode.append;
	t_u64a		flags;

	flags = xft_tern(writes, xft_o_wronly, xft_o_rdonly);
	flags = xft_tern(writes && mode.read, xft_o_rdwr, flags);
	flags |= xft_tern(mode.create || mode.exclusive, xft_o_creat, 0);
	flags |= xft_tern(mode.exclusive, xft_o_excl, 0);
	flags |= xft_tern(mode.truncate, xft_o_trunc, 0);
	flags |= xft_tern(mode.append, xft_o_append, 0);
	return ((int)flags);
}

__attribute__((__always_inline__, __nonnull__(1, 3), __used__))
inline t_result	xft_open_file(t_blk8r path, t_fileopen_mode mode, t_fd *fd)
{
	const int		flags = xft__open_flags(mode);
	int				raw;
	t_xft_sysres	ret;

	raw = -1;
	ret = xft_sys_repeat;
	while (ret == xft_sys_repeat)
		ret = xft_open((const char *)path, flags, xft_open_0666, &raw);
	if (__builtin_expect(ret != xft_sys_ok, 0))
		return (KO);
	*fd = (t_fd)raw;
	return (OK);
}

__attribute__((__always_inline__, __used__))
inline t_result	xft_close_file(t_fd fd)
{
	return ((t_result)(xft_close((int)fd) == xft_sys_ok));
}

#endif
