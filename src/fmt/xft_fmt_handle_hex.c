/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fmt_handle_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:17:52 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/19 23:24:17 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_fmt.h>

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_result	xft_fmt_handle_hex(t_writer *__restrict__ const writer,
	t_u64 value, bool is_lowercase)
{
	t_u8		inner_buffer[20];
	t_u8		h;
	t_size		i;

	i = 20;
	if (value == 0)
		inner_buffer[--i] = '0';
	while (value)
	{
		h = (char)(value & 0x0F);
		inner_buffer[--i] = (char)((h + '0' + ((h + 6) >> 4) * 7)
				| is_lowercase << 5);
		value >>= 4;
	}
	return (xft_writer_write(writer, xft_fatptr(inner_buffer + i, 20 - i)));
}
