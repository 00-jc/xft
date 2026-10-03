/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mmap_commit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 17:45:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 17:45:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <syscalls.h>

#ifdef __linux__

__attribute__((__nonnull__(1), __always_inline__, __used__, const))
inline t_result	xft_mmap_commit(t_any ptr, t_size size,
	t_u64a prot, t_u64a flags_extra)
{
	(void)ptr;
	(void)size;
	(void)prot;
	(void)flags_extra;
	return (OK);
}

#endif
