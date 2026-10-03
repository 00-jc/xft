/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 16:00:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 23:04:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "xft_p_fmt.h"

__attribute__((__nonnull__(1, 3)))
static inline t_result	xft_fmt_manage(t_writer *__restrict__ const writer,
	t_u8 c, t_u64 **value)
{
	t_u64	aux[2];

	if (*value == nullptr)
		__builtin_unreachable();
	if (c == 'x' || c == 'X' || c == 'p')
		return (xft_fmt_handle_hex(writer, *(*value)++, c == 'x' || c == 'p'));
	else if (c == 'f')
		return (xft_fmt_handle_double(writer, *(*value)++));
	else if (c == 's')
	{
		aux[0] = *(*value)++;
		aux[1] = *(*value)++;
		return (xft_fmt_handle_slice(writer, aux[0], aux[1]));
	}
	else if (c == 'q' || c == 'u' || c == 'w' || c == 'b')
		return (xft_fmt_handle_unsigned(writer, *(*value)++, c));
	else if (c == 'i' || c == 'd' || c == 'o' || c == 'y')
		return (xft_fmt_handle_signed(writer, *(*value)++, c));
	else if (c == '%')
		return (xft_writer_write(writer, xft_fatptr((t_u8 *)"%", 1)));
	else
		return (KO);
}

__attribute__((__nonnull__(1, 3)))
t_result	xft_fmt_writer(t_writer *writer,
	t_buffer fmt, t_u64 *values)
{
	t_size								maxptr;
	const t_u8	*restrict				subst;
	const t_u8	*restrict				start;

	if (fmt.mem == nullptr)
		__builtin_unreachable();
	maxptr = (t_uptr)fmt.mem + fmt.size;
	start = fmt.mem;
	subst = xft_memchr(fmt.mem, '%', fmt.size);
	while (subst && (t_uptr)subst < maxptr)
	{
		if (__builtin_expect(xft_writer_write(writer, xft_fatptr(start,
						(t_uptr)subst++ - (t_uptr)start)) == KO, 0))
			return (KO);
		if (__builtin_expect((t_uptr)subst == maxptr, 0))
			break ;
		if (__builtin_expect(xft_fmt_manage(writer, *subst, &values) == KO, 0))
			return (KO);
		start = ++subst;
		subst = xft_memchr(start, '%', maxptr - (t_uptr)start);
	}
	return (xft_writer_write(writer,
			xft_fatptr(start, maxptr - (t_uptr)start)));
}
