/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_handle_unsigned.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:27:35 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 17:40:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "mem.h"
#include "private/ft_p_fmt.h"

__attribute__((const, __always_inline__))
inline t_u64	ft_get_max(t_u8 c)
{
	if (c == 'q')
		return (UINT64_MAX);
	else if (c == 'u')
		return (UINT32_MAX);
	else if (c == 'w')
		return (UINT16_MAX);
	else if (c == 'b')
		return (UINT8_MAX);
	else
		return (0);
}

__attribute__((__nonnull__(1), __always_inline__))
inline t_result	ft_fmt_handle_unsigned(t_writer *__restrict__ const writer,
	t_u64 value, t_u8 c)
{
	t_u8	inner_buffer[20];
	t_size	i;
	t_u64	tmp;

	value &= ft_get_max(c);
	i = 20;
	if (value == 0)
		inner_buffer[--i] = '0';
	while (value)
	{
		tmp = (t_u128a)value * 0xCCCCCCCCCCCCCCCDULL >> 67;
		inner_buffer[--i] = (char)((value - ((tmp << 3) + (tmp << 1))) + '0');
		value = tmp;
	}
	return (ft_writer_write(writer, ft_fatptr(inner_buffer + i, 20 - i)));
}
