/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 13:52:33 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# define NOMINMAX
# include <windows.h>
# pragma comment(lib, "kernel32.lib")

# ifndef S_IFREG
#  define S_IFIFO	0010000
#  define S_IFCHR	0020000
#  define S_IFDIR	0040000
#  define S_IFREG	0100000
# endif

# define XFT_P_EPOCH_DIFF		116444736000000000LL
# define XFT_P_TICKS_PER_SEC		10000000LL
# define XFT_P_NSEC_PER_SEC		1000000000LL

__attribute__((__always_inline__, unused, __used__))
inline t_timespec	xft_p_wintime(LARGE_INTEGER time)
{
	t_timespec	ts;
	t_i64		ticks;
	t_i64		sec;
	t_i64		nsec;

	ticks = time.QuadPart - XFT_P_EPOCH_DIFF;
	sec = ticks / XFT_P_TICKS_PER_SEC;
	nsec = (ticks % XFT_P_TICKS_PER_SEC) * 100;
	if (nsec < 0)
	{
		sec -= 1;
		nsec += XFT_P_NSEC_PER_SEC;
	}
	ts.tv_sec = sec;
	ts.tv_nsec = nsec;
	return (ts);
}

__attribute__((__always_inline__, unused, __used__))
inline t_mode	xft_p_winmode(DWORD attrs)
{
	t_mode	acc;

	acc = (t_mode)xft_tern(attrs & FILE_ATTRIBUTE_READONLY, 0444, 0666);
	acc |= (t_mode)xft_tern(attrs & FILE_ATTRIBUTE_DIRECTORY,
			S_IFDIR | 0111, S_IFREG);
	return (acc);
}

__attribute__((__always_inline__, __nonnull__(2), unused, __used__))
inline int	xft_p_diskstat(HANDLE h, t_stat *statbuf)
{
	BY_HANDLE_FILE_INFORMATION	info;
	FILE_BASIC_INFO				basic;
	FILE_STANDARD_INFO			std;
	BOOL						ok;

	ok = GetFileInformationByHandle(h, &info)
		&& GetFileInformationByHandleEx(h, FileBasicInfo, &basic, sizeof(basic))
		&& GetFileInformationByHandleEx(h, FileStandardInfo, &std, sizeof(std));
	if (__builtin_expect(!ok, 0))
		return (-1);
	*statbuf = (t_stat){0};
	statbuf->st_dev = info.dwVolumeSerialNumber;
	statbuf->st_ino = ((t_u64)info.nFileIndexHigh << 32) | info.nFileIndexLow;
	statbuf->st_nlink = info.nNumberOfLinks;
	statbuf->st_mode = xft_p_winmode(info.dwFileAttributes);
	statbuf->st_size = ((t_u64)info.nFileSizeHigh << 32) | info.nFileSizeLow;
	statbuf->st_blksize = 4096;
	statbuf->st_blocks = std.AllocationSize.QuadPart / 512;
	statbuf->st_atim = xft_p_wintime(basic.LastAccessTime);
	statbuf->st_mtim = xft_p_wintime(basic.LastWriteTime);
	statbuf->st_ctim = xft_p_wintime(basic.ChangeTime);
	return (0);
}

__attribute__((__always_inline__, __nonnull__(2), unused, __used__))
inline int	xft_p_devstat(DWORD type, t_stat *statbuf)
{
	*statbuf = (t_stat){0};
	statbuf->st_mode = (t_mode)xft_tern(type == FILE_TYPE_PIPE,
			S_IFIFO | 0666, S_IFCHR | 0666);
	statbuf->st_nlink = 1;
	statbuf->st_blksize = 4096;
	return (0);
}

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline int	xft_stat(const char *restrict path, t_stat *statbuf)
{
	HANDLE	h;
	DWORD	type;
	int		result;

	h = CreateFileA(path, 0,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			(t_any)0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, (t_any)0);
	if (__builtin_expect(h == INVALID_HANDLE_VALUE, 0))
		return (-1);
	type = GetFileType(h);
	if (type == FILE_TYPE_DISK)
		result = xft_p_diskstat(h, statbuf);
	else
		result = xft_p_devstat(type, statbuf);
	CloseHandle(h);
	return (result);
}

#endif
