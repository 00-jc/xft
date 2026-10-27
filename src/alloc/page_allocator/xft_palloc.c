/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_palloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/25 22:23:40 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_palloc.h>

__attribute__((__always_inline__, __used__))
inline t_buffer	xft_palloc(t_size size)
{
	t_buffer	b;

	b = xft_palloc_reserve(size);
	if (b.mem && !xft_palloc_commit(b.mem, b.size))
	{
		xft_palloc_free(b);
		b.mem = nullptr;
	}
	return (b);
}
