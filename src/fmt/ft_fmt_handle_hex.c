/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_handle_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:17:52 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 17:37:10 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_fmt.h"

__attribute__((__nonnull__(1), __always_inline__))
inline t_result	ft_fmt_handle_hex(t_writer *__restrict__ const writer,
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
				| is_lowercase);
		value >>= 4;
	}
	return (ft_writer_write(writer, ft_fatptr(inner_buffer + i, 20 - i)));
}
