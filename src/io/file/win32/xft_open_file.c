/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_open_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 22:42:26 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/27 23:02:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/files.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__always_inline__, __const__))
static inline DWORD	xft__access(t_fileopen_mode mode)
{
	DWORD	access;

	access = 0;
	if (mode.read)
		access |= GENERIC_READ;
	if (mode.append)
		access |= FILE_GENERIC_WRITE & ~(DWORD)FILE_WRITE_DATA;
	else if (mode.write)
		access |= GENERIC_WRITE;
	return (access);
}

__attribute__((__always_inline__, __const__))
static inline DWORD	xft__disposition(t_fileopen_mode mode)
{
	if (mode.exclusive)
		return (CREATE_NEW);
	if (mode.create && mode.truncate)
		return (CREATE_ALWAYS);
	if (mode.create)
		return (OPEN_ALWAYS);
	if (mode.truncate)
		return (TRUNCATE_EXISTING);
	return (OPEN_EXISTING);
}

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_fd	xft_open_file(t_blk8r path, t_fileopen_mode mode)
{
	return ((t_fd)CreateFileA((LPCSTR)path, xft__access(mode),
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
			xft__disposition(mode), FILE_ATTRIBUTE_NORMAL, nullptr));
}

__attribute__((__always_inline__, __used__))
inline t_fd	xft_close_file(t_fd fd)
{
	if (__builtin_expect(!CloseHandle((HANDLE)(intptr_t)fd), 0))
		return ((t_fd)INVALID_HANDLE_VALUE);
	return (0);
}

#endif
