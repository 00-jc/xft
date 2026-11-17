/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_str_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 02:07:27 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/str.h>

__attribute__((__nonnull__(2)))
t_result	xft_str_push_back(t_allocator allocator,
		t_str *restrict const str, const t_u8 byte)
{
	if (str->buf.mem == nullptr || allocator.allocator == nullptr)
		__builtin_unreachable();
	if (__builtin_expect(str->buf.size + 1 >= str->buf.capacity
			&& !xft_str_reserve(allocator, str,
				xft_tern_s(str->buf.capacity, str->buf.capacity << 1, 4)), 0))
		return (KO);
	str->buf.mem[str->buf.size++] = byte;
	str->buf.mem[str->buf.size] = 0;
	return (OK);
}
