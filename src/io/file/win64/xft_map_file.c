/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_map_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__nonnull__(1)))
t_buffer	xft_map_file_into_memory(const char *name)
{
	HANDLE			file;
	HANDLE			map;
	LARGE_INTEGER	size;
	t_any			ptr;

	file = CreateFileA(name, GENERIC_READ, FILE_SHARE_READ, nullptr,
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

void	xft_unmap_file_from_memory(t_buffer buffer)
{
	if (buffer.mem == nullptr)
		__builtin_unreachable();
	UnmapViewOfFile(buffer.mem);
}

#endif
