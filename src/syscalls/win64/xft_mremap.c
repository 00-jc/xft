/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mremap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"
#include "syscalls.h"
#include "bmi.h"
#include "mem.h"

#ifdef _WIN64

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline t_any	xft_mremap(t_size size, t_size new_size,
	t_any addr, t_u64a flags_extra)
{
	t_any	ret;

	ret = xft_mmap(new_size, PROT_READ | PROT_WRITE, flags_extra);
	if (__builtin_expect(xft_map_failed(ret), 0))
		return (ret);
	if (__builtin_expect(!xft_mmap_commit(ret, new_size,
				PROT_READ | PROT_WRITE, flags_extra), 0))
	{
		xft_munmap(ret, new_size);
		return ((t_any)MAP_FAILED);
	}
	xft_memcpy(ret, addr, xft_tern(size < new_size, size, new_size));
	xft_munmap(addr, size);
	return (ret);
}

#endif
