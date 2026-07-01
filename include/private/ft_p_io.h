/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_io.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 23:17:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_IO_H
# define FT_P_IO_H

# include "io.h"

t_result		ft_stream_flush(void *__restrict__ const writer)\
					__attribute__((__nonnull__(1)));

t_result		ft_stream_drain(void *__restrict__ const writer,\
					t_iovec *__restrict__ bufs, t_size nbufs)\
					__attribute__((__always_inline__, __nonnull__(1, 2)));

t_result		ft_stream_fill(void *__restrict__ const reader)\
					__attribute__((__always_inline__, __nonnull__(1)));

t_result		ft_stream_unbuffered_fill(void *reader, t_u8 *dst,\
					const t_size len, t_size *total)\
					__attribute__((__nonnull__(1, 2, 4)));

t_result		ft_raw_flush(void *__restrict__ const writer)\
					__attribute__((__nonnull__(1)));

t_result		ft_raw_drain(void *__restrict__ const writer,\
					t_iovec *__restrict__ bufs, t_size nbufs)\
					__attribute__((__always_inline__, __nonnull__(1, 2)));

t_result		ft_raw_fill(void *__restrict__ const reader)\
					__attribute__((__always_inline__, __nonnull__(1)));

t_result		ft_raw_unbuffered_fill(void *reader, t_u8 *dst,\
					const t_size len, t_size *total)\
					__attribute__((__nonnull__(1, 2, 4)));

#endif
