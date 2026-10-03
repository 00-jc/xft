/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_writev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 09:05:43 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 10:28:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"

#ifdef _WIN64

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_ssize	xft_writev(int fd, t_iovec *restrict const buffers, t_size len)
{
	t_size	i;
	t_ssize	ret;
	t_ssize	total;

	i = 0;
	total = 0;
	while (i < len)
	{
		ret = 0;
		if (buffers[i].size)
			ret = xft_write(fd, buffers[i].mem, buffers[i].size);
		if (__builtin_expect(ret < 0 && !total, 0))
			return (-1);
		if (__builtin_expect(ret < 0, 0))
			return (total);
		total += ret;
		if ((t_size)ret < buffers[i++].size)
			break ;
	}
	return (total);
}

#endif
