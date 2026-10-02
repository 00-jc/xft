/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 00:26:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# pragma comment(lib, "kernel32.lib")

__attribute__((__always_inline__, const, unused, __used__))
inline DWORD	xft_p_mmap_prot(t_u64a prot)
{
	DWORD	acc;

	acc = PAGE_NOACCESS;
	acc = (DWORD)xft_tern(prot & PROT_READ, PAGE_READONLY, acc);
	acc = (DWORD)xft_tern(prot & PROT_WRITE, PAGE_READWRITE, acc);
	acc <<= xft_tern(prot & PROT_EXEC, 4, 0);
	return (acc);
}

__attribute__((__always_inline__, __used__))
inline t_any	xft_mmap(t_size size, t_u64a prot, t_u64a flags_extra)
{
	t_any	ret;

	(void)flags_extra;
	ret = VirtualAlloc((t_any)0, size, MEM_COMMIT | MEM_RESERVE,
			xft_p_mmap_prot(prot));
	return ((t_any)xft_tern(ret != (t_any)0, (t_u64a)ret,
			(t_u64a)MAP_FAILED));
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_munmap(t_any restrict const mem, t_size size)
{
	(void)size;
	if (!VirtualFree(mem, 0, MEM_RELEASE))
		UnmapViewOfFile(mem);
}

#endif
