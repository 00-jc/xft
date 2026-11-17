/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_str_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/str.h>

__attribute__((__nonnull__(1)))
t_result	xft_str_remove(t_str *restrict const v, t_size i)
{
	t_u8	*start;
	t_size	len;

	if (v->buf.mem == nullptr)
		__builtin_unreachable();
	if (v->buf.size <= i)
		return (KO);
	start = v->buf.mem + i;
	len = v->buf.size - i;
	xft_memmove(start, start + 1, len);
	--v->buf.size;
	return (OK);
}
