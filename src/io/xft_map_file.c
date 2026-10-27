/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_map_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 09:06:33 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 23:14:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>

#if defined(__linux__)
# include <xft/xft_p_syscalls.h>
#elif defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif

#if defined(__linux__)

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_buffer	xft_map_file(const t_u8 *__restrict__ const name, t_u32 flags)
{
	t_i32	fd;
	t_stat	stat;
	t_any	ptr;

	if (__builtin_expect(xft_stat((t_any)name, &stat), 0))
		return ((t_buffer){0});
	fd = xft_open((t_any)name, flags, 0);
	if (__builtin_expect(fd == -1, 0))
		return ((t_buffer){0});
	ptr = xft_fmap(stat.st_size, xft_prot_read, xft_map_private, fd);
	if (__builtin_expect(xft_map_failed(ptr), 0))
		return ((void)xft_close(fd), (t_buffer){0});
	xft_close(fd);
	return ((t_buffer){.size = stat.st_size, .mem = ptr});
}

__attribute__((__always_inline__, __used__))
inline void	xft_unmap_file(t_buffer file)
{
	xft_munmap(file.mem, file.size);
}

#elif defined(_WIN32)

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline t_buffer	xft_map_file(const t_u8 *__restrict__ const name, t_u32 flags)
{
	HANDLE			file;
	HANDLE			map;
	LARGE_INTEGER	size;
	t_any			ptr;

	(void)flags;
	file = CreateFileA((LPCSTR)name, GENERIC_READ, FILE_SHARE_READ, nullptr,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (__builtin_expect(file == INVALID_HANDLE_VALUE, 0))
		return ((t_buffer){0});
	if (__builtin_expect(!GetFileSizeEx(file, &size), 0))
		return ((void)CloseHandle(file), (t_buffer){0});
	map = CreateFileMappingA(file, nullptr, PAGE_READONLY, 0, 0, nullptr);
	CloseHandle(file);
	if (__builtin_expect(!map, 0))
		return ((t_buffer){0});
	ptr = MapViewOfFile(map, FILE_MAP_READ, 0, 0, 0);
	CloseHandle(map);
	if (__builtin_expect(!ptr, 0))
		return ((t_buffer){0});
	return ((t_buffer){.size = (t_size)size.QuadPart, .mem = ptr});
}

__attribute__((__always_inline__, __used__))
inline void	xft_unmap_file(t_buffer file)
{
	UnmapViewOfFile(file.mem);
}

#endif
