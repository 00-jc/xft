/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_handle_signed.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:42:34 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 17:51:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "mem.h"
#include "private/ft_p_fmt.h"

__attribute__((const, __always_inline__))
inline t_i64	ft_sign_extend(t_u64 value, t_u8 c)
{
	if (c == 'y')
		return ((t_i64)(value << 56) >> 56);
	else if (c == 'o')
		return ((t_i64)(value << 48) >> 48);
	else if (c == 'd')
		return ((t_i64)(value << 32) >> 32);
	else
		return ((t_i64)value);
}

__attribute__((__nonnull__(1), __always_inline__))
inline t_result	ft_fmt_handle_signed(t_writer *__restrict__ const writer,
	t_u64 value, t_u8 c)
{
	t_u8	inner_buffer[20];
	t_size	i;
	t_u64	mag;
	t_u64	tmp;
	bool	neg;

	neg = ft_sign_extend(value, c) < 0;
	mag = ft_tern(neg, -((t_u64)ft_sign_extend(value, c)),
			ft_sign_extend(value, c));
	i = 20;
	if (mag == 0)
		inner_buffer[--i] = '0';
	while (mag)
	{
		tmp = (t_u128a)mag * 0xCCCCCCCCCCCCCCCDULL >> 67;
		inner_buffer[--i] = (char)((mag - ((tmp << 3) + (tmp << 1))) + '0');
		mag = tmp;
	}
	if (neg)
		inner_buffer[--i] = '-';
	return (ft_writer_write(writer, ft_fatptr(inner_buffer + i, 20 - i)));
}
