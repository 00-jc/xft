/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fatptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:02:15 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/12 16:36:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

__attribute__((__always_inline__, const))
inline t_buffer	ft_fatptr(t_blk8r mem, t_size size)
{
	return ((t_buffer){.mem = (t_u8 *)mem, .size = size});
}
