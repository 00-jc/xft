/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 12:32:34 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 13:24:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_io.h"
#include "types/io_types.h"

__attribute__((__always_inline__, __nonnull__(1, 2)))
inline void	ft_sync_iovecs(t_iovec *__restrict__ *__restrict__ bufs,
	t_size *__restrict__ nbufs, t_size written)
{
	t_size	i;

	i = 0;
	if (*bufs == nullptr)
		__builtin_unreachable();
	while (i < *nbufs && written >= (*bufs)[i].size)
		written -= (*bufs)[i++].size;
	*bufs += i;
	*nbufs -= i;
	if (*nbufs != 0)
	{
		if ((*bufs)[0].mem == nullptr)
			__builtin_unreachable();
		(*bufs)[0].mem += written;
		(*bufs)[0].size -= written;
	}
}

__attribute__((__always_inline__, __nonnull__(1, 2)))
inline t_result	ft_stream_drain(void *__restrict const writer,
	t_iovec *__restrict__ bufs, t_size nbufs)
{
	t_writer *__restrict__ const		w = writer;
	t_ssize								ret;

	while (nbufs != 0)
	{
		ret = ft_writev(w->as.fs_writer.fd, bufs, nbufs);
		if (__builtin_expect(ret <= 0, 0))
			return (KO);
		ft_sync_iovecs(&bufs, &nbufs, (t_size)ret);
	}
	w->end = 0;
	return (OK);
}
