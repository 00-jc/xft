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
#include "private/ft_p_fmt.h"

//	%x -> hex lower (u64 / whole value slot) 
//	%X -> hex upper (u64 / whole value slot)
//	%p -> hex lower (u64 / whole value slot)
//	%b -> u8
//	%y -> i8
//	%w -> u16
//	%o -> i16
//	%u -> u32
//	%d -> i32
//	%q -> u64
//	%i -> i64
//	%s -> slice (ptr + len, takes 2 args)
//	%f -> double (reinterpret cast from value)

__attribute__((__nonnull__(1, 3)))
static inline t_result	ft_fmt_manage(t_writer *__restrict__ const writer,
	t_u8 c, t_u64 **value)
{
	t_u64	aux[2];

	if (*value == nullptr)
		__builtin_unreachable();
	if (c == 'x' || c == 'X' || c == 'p')
		return (ft_fmt_handle_hex(writer, *(*value)++, c == 'x' || c == 'p'));
	else if (c == 'f')
		return (ft_fmt_handle_double(writer, *(*value)++));
	else if (c == 's')
	{
		aux[0] = *(*value)++;
		aux[1] = *(*value)++;
		return (ft_fmt_handle_slice(writer, aux[0], aux[1]));
	}
	else if (c == 'q' || c == 'u' || c == 'w' || c == 'b')
		return (ft_fmt_handle_unsigned(writer, *(*value)++, c));
	else if (c == 'i' || c == 'd' || c == 'o' || c == 'y')
		return (ft_fmt_handle_signed(writer, *(*value)++, c));
	else if (c == '%')
		return (ft_writer_write(writer, ft_fatptr((t_u8 *)"%", 1)));
	else
		return (KO);
}

// if you don't have a format don't call write
__attribute__((__nonnull__(1, 3)))
t_result	ft_fmt_writer(t_writer *writer,
	t_buffer fmt, t_u64 *values)
{
	t_size								maxptr;
	const t_u8	*restrict				subst;
	const t_u8	*restrict				start;

	if (fmt.mem == nullptr)
		__builtin_unreachable();
	maxptr = (t_uptr)fmt.mem + fmt.size;
	start = fmt.mem;
	subst = ft_memchr(fmt.mem, '%', fmt.size);
	while (subst && (t_uptr)subst < maxptr)
	{
		if (__builtin_expect(ft_writer_write(writer, ft_fatptr(start,
						(t_uptr)subst++ - (t_uptr)start)) == KO, 0))
			return (KO);
		if (__builtin_expect((t_uptr)subst == maxptr, 0))
			break ;
		if (__builtin_expect(ft_fmt_manage(writer, *subst, &values) == KO, 0))
			return (KO);
		start = ++subst;
		subst = ft_memchr(start, '%', maxptr - (t_uptr)start);
	}
	return (ft_writer_write(writer, ft_fatptr(start, maxptr - (t_uptr)start)));
}
