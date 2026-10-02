/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 14:43:03 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 14:43:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__always_inline__, const, unused, __used__))
inline DWORD	xft_p_open_access(int flags)
{
	DWORD	acc;
	DWORD	write;
	int		mode;

	mode = flags & O_ACCMODE;
	write = (DWORD)xft_tern(flags & O_APPEND,
			FILE_GENERIC_WRITE & ~FILE_WRITE_DATA, GENERIC_WRITE);
	acc = (DWORD)xft_tern(mode != O_WRONLY, GENERIC_READ, 0);
	acc |= (DWORD)xft_tern(mode != O_RDONLY, write, 0);
	return (acc);
}

__attribute__((__always_inline__, const, unused, __used__))
inline DWORD	xft_p_open_disposition(int flags)
{
	DWORD	acc;

	acc = OPEN_EXISTING;
	acc = (DWORD)xft_tern(flags & O_TRUNC, TRUNCATE_EXISTING, acc);
	acc = (DWORD)xft_tern(flags & O_CREAT, OPEN_ALWAYS, acc);
	acc = (DWORD)xft_tern((flags & O_CREAT) && (flags & O_TRUNC),
			CREATE_ALWAYS, acc);
	acc = (DWORD)xft_tern((flags & O_CREAT) && (flags & O_EXCL),
			CREATE_NEW, acc);
	return (acc);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline int	xft_open(const char *restrict path, int flags)
{
	HANDLE	fd;

	fd = CreateFileA((t_any)path, xft_p_open_access(flags),
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			(t_any)0, xft_p_open_disposition(flags),
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS, (t_any)0);
	return ((int)(intptr_t)fd);
}

#endif
