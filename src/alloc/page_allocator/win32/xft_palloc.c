/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_palloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/25 22:23:40 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_palloc.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__always_inline__, __used__))
inline t_buffer	xft_palloc_reserve(t_size size)
{
	size = (size + 4095) & ~(t_size)4095;
	return (xft_fatptr(VirtualAlloc(nullptr, size, MEM_RESERVE,
				PAGE_READWRITE), size));
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_result	xft_palloc_commit(t_any ptr, t_size size)
{
	return ((t_result)(VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE)
		!= nullptr));
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_result	xft_palloc_guard(t_any ptr, t_size size)
{
	DWORD	old;

	return ((t_result)(VirtualProtect(ptr, size, PAGE_NOACCESS, &old) != 0));
}

__attribute__((__always_inline__, __used__))
inline t_buffer	xft_palloc_resize(t_buffer b, t_size new_size)
{
	t_buffer	n;

	new_size = (new_size + 4095) & ~(t_size)4095;
	if (__builtin_expect(new_size == b.size, 1))
		return (b);
	n = xft_palloc(new_size);
	if (__builtin_expect(n.mem == nullptr, 0))
		return (xft_fatptr(nullptr, 0));
	xft_memcpy(n.mem, b.mem, xft_tern_s(b.size < n.size, b.size, n.size));
	xft_palloc_free(b);
	return (n);
}

__attribute__((__always_inline__, __used__))
inline void	xft_palloc_free(t_buffer b)
{
	VirtualFree(b.mem, 0, MEM_RELEASE);
}

#endif
