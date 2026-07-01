/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_handle_slice.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:53:39 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 17:54:38 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_fmt.h"

__attribute__((__nonnull__(1), __always_inline__))
inline t_result	ft_fmt_handle_slice(t_writer *__restrict__ const writer,
	t_u64 ptr, t_u64 len)
{
	return (ft_writer_write(writer, ft_fatptr((const t_u8 *)ptr, len)));
}
