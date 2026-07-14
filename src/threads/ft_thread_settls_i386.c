/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_settls_i386.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "private/ft_p_thread.h"

#if defined(__i386__)

__attribute__((__always_inline__, unused, __nonnull__(2)))
inline t_uptr	ft__settls_arg(t_uptr tp, t_user_desc *__restrict__ const ud)
{
	ud->entry_number = (t_u32)-1;
	ud->base_addr = (t_u32)tp;
	ud->limit = 0xfffff;
	ud->seg_32bit = 1;
	ud->contents = 0;
	ud->read_exec_only = 0;
	ud->limit_in_pages = 1;
	ud->seg_not_present = 0;
	ud->useable = 1;
	return ((t_uptr)ud);
}

#endif
