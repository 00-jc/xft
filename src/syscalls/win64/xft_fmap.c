/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__always_inline__, __used__))
inline t_any	xft_fmap(t_size size, int fd)
{
	HANDLE	map;
	t_any	ret;

	map = CreateFileMappingA((HANDLE)(intptr_t)fd, (t_any)0, PAGE_READONLY,
			0, 0, (t_any)0);
	if (__builtin_expect(!map, 0))
		return ((t_any)(intptr_t)MAP_FAILED);
	ret = MapViewOfFile(map, FILE_MAP_READ, 0, 0, size);
	CloseHandle(map);
	return ((t_any)xft_tern(ret != (t_any)0, (t_u64a)ret,
			(t_u64a)MAP_FAILED));
}

#endif
