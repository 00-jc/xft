/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fmt_handle_slice.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:53:39 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 17:54:38 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_fmt.h"

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_result	xft_fmt_handle_slice(t_writer *__restrict__ const writer,
	t_u64 ptr, t_u64 len)
{
	return (xft_writer_write(writer, xft_fatptr((const t_u8 *)ptr, len)));
}
