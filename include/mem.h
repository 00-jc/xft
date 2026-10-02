/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 00:51:38 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include "primitives.h"
# include "bmi.h"

# define LONES_64 			0x0101010101010101ULL
# define HIGHS_64	 		0x8080808080808080ULL

# ifndef XFT_PAGE_ALIGN
#  define XFT_PAGE_ALIGN 0x1000ULL
# endif

void			xft_bzero(t_any __restrict__ ptr, t_size n)\
					__attribute__((__nonnull__(1)));

void			*xft_memset(t_any __restrict__ s, const t_i32 c, t_size n)\
					__attribute__((__nonnull__(1)));

void			*xft_memcpy(t_any __restrict__ dest,
					t_cany __restrict__ src, t_size n)\
					__attribute__((__nonnull__(1, 2), __hot__));

void			xft_memtake(t_any __restrict__ dest,
					t_any __restrict__ src, t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_memmove(t_any dest, t_cany src, t_size n)\
					__attribute__((__nonnull__(1, 2), __hot__));

t_any			xft_memchr(t_cany __restrict__ ptr, int c, t_size n)\
					__attribute__((__nonnull__(1)));

t_ssize			xft_memcmp(t_cany __restrict__ const dest,
					t_cany __restrict__ src, t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_membroadcast(t_any dst, t_any src, t_size chunks, t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_prefetch0(t_cany __restrict__ const ptr, t_size size)\
					__attribute__((__nonnull__(1)));

void			xft_prefetch1(t_cany __restrict__ const ptr, t_size size)\
					__attribute__((__nonnull__(1)));

void			xft_prefetch2(t_cany __restrict__ const ptr, t_size size)\
					__attribute__((__nonnull__(1)));

void			xft_prefetchnta(t_cany __restrict__ const ptr, t_size size)\
					__attribute__((__nonnull__(1)));

t_any			xft_overlap(t_cany __restrict__ ptr,\
					t_size chunk_size, t_size rem_size)\
					__attribute__((__nonnull__(1), const));

t_buffer		xft_fatptr(t_blk8r mem, t_size size)\
					__attribute__((const));

t_any			xft_align_fwd(t_any ptr, const t_size align)\
					__attribute__((const, __nonnull__(1),\
					__returns_nonnull__));

t_any			xft_align_bkw(t_any ptr, const t_size align)\
					__attribute__((const, __nonnull__(1),\
					__returns_nonnull__));

void			xft_stfence(void);
void			xft_ldfence(void);

#endif
