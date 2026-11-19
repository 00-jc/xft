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

# include <xft/bmi.h>
# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__always_inline__, __const__))
static inline DWORD	xft__access(t_fileopen_mode mode)
{
	const DWORD	append = FILE_GENERIC_WRITE & ~(DWORD)FILE_WRITE_DATA;
	t_u64a		access;

	access = xft_tern(mode.write, GENERIC_WRITE, 0);
	access = xft_tern(mode.append, append, access);
	access |= xft_tern(mode.read, GENERIC_READ, 0);
	return ((DWORD)access);
}

__attribute__((__always_inline__, __const__))
static inline DWORD	xft__disposition(t_fileopen_mode mode)
{
	const bool	replace = mode.create && mode.truncate;
	t_u64a		disposition;

	disposition = xft_tern(mode.truncate, TRUNCATE_EXISTING, OPEN_EXISTING);
	disposition = xft_tern(mode.create, OPEN_ALWAYS, disposition);
	disposition = xft_tern(replace, CREATE_ALWAYS, disposition);
	disposition = xft_tern(mode.exclusive, CREATE_NEW, disposition);
	return ((DWORD)disposition);
}

__attribute__((__always_inline__, __nonnull__(1, 3), __used__))
inline t_result	xft_open_file(t_blk8r path, t_fileopen_mode mode, t_fd *fd)
{
	const DWORD	share = FILE_SHARE_READ | FILE_SHARE_WRITE
		| FILE_SHARE_DELETE;
	HANDLE		file;

	file = CreateFileA((LPCSTR)path, xft__access(mode), share, nullptr,
			xft__disposition(mode), FILE_ATTRIBUTE_NORMAL, nullptr);
	if (__builtin_expect(file == INVALID_HANDLE_VALUE, 0))
		return ((t_result){.ok = KO, .err = xft_err_none});
	*fd = (t_fd)file;
	return ((t_result){.ok = OK});
}

__attribute__((__always_inline__, __used__))
inline t_result	xft_close_file(t_fd fd)
{
	return ((t_result){.ok = (CloseHandle((HANDLE)fd) != 0)});
}

#endif
