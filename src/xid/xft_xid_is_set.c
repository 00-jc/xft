/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_xid_is_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 05:15:40 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 05:20:35 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xid.h"
#include "ctype.h"

// last range whose lo is <= cp, branchless; set must not be empty
__attribute__((__pure__, __always_inline__, __hot__, __nonnull__(1)))
static inline bool	xft__xid_in_set(const t_u32 (*set)[2], t_size len,
	t_u32 cp)
{
	t_size	base;
	t_size	half;

	base = 0;
	while (len > 1)
	{
		half = len >> 1;
		base += half * (set[base + half][0] <= cp);
		len -= half;
	}
	return ((set[base][0] <= cp) & (cp <= set[base][1]));
}

__attribute__((__pure__, __always_inline__, __used__, __hot__))
inline bool	xft_xid_is_start(t_u32 cp)
{
	if (__builtin_expect(cp < 0x80, 1))
		return (xft_isalpha((int)cp) | (cp == '_'));
	return (xft__xid_in_set(g_xid_start, g_xid_start_len, cp));
}

__attribute__((__pure__, __always_inline__, __used__, __hot__))
inline bool	xft_xid_is_continue(t_u32 cp)
{
	if (__builtin_expect(cp < 0x80, 1))
		return (xft_isalnum((int)cp) | (cp == '_'));
	return (xft__xid_in_set(g_xid_continue, g_xid_continue_len, cp));
}
