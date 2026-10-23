/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_mem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/23 13:02:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_MEM_H
# define XFT_P_MEM_H

# include "mem.h"
# include "xft_p_asm.h"

# if !defined(XFT_LLC_SIZE) || XFT_LLC_SIZE == 0
#  define XFT_LLC_SIZE 16777216ULL
# endif

typedef struct s_t_f64_size
{
	t_size		i;
	t_size		blks;
}	t_t_f64_size;

void			*xft__memcpy(t_any __restrict__ dest,
					t_cany __restrict__ const src, t_size n)\
					__attribute__((__nonnull__(1, 2), __hot__, __noinline__,\
						__returns_nonnull__));

void			xft_memcpy_naive(t_any __restrict__ dest,
					t_cany __restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_memcpy_512_huge(t_any __restrict__ dest,\
					t_cany __restrict__ const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_memmove_naive(t_any dest, t_cany const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_memmove_512_fwd(t_any dest, t_cany const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_memmove_512_huge(t_any dest, t_cany const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_memcpy_64(t_any __restrict__ dest,
					t_cany __restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_memmove_64(t_any dest, t_cany const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_memset_naive(t_any __restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));
void			xft_memset_64(t_any __restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			xft_memcpy_128(t_any __restrict__ dest,
					t_cany __restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));
void			xft_memcpy_256(t_any __restrict__ dest,
					t_cany __restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));
void			xft_memcpy_512(t_any __restrict__ dest,
					t_cany __restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_memmove_128(t_any dest, t_cany const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));
void			xft_memmove_256(t_any dest, t_cany const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));
void			xft_memmove_512(t_any dest, t_cany const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_movsb(t_any __restrict__ dest,
					t_cany __restrict__ src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_movsq(t_any __restrict__ dest,
					t_cany __restrict__ src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_memset_128(t_any __restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			xft_memset_256(t_any __restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			xft_memset_512(t_any __restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			xft_memset_512_huge(t_any __restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

t_any			xft_memchr_short(t_cany __restrict__ const ptr,
					t_u8 c, t_size n)\
					__attribute__((__nonnull__(1)));

t_any			xft_memchr_tail(t_cany __restrict__ const ptr,
					t_u8 c, t_size n)\
					__attribute__((__nonnull__(1)));

t_ssize			xft_memcmp_short(t_cany __restrict__ const ptr1,
					t_cany __restrict__ const ptr2, t_size n)\
					__attribute__((__nonnull__(1, 2)));

t_ssize			xft_memcmp_tail(t_cany __restrict__ const ptr1,
					t_cany __restrict__ const ptr2, t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			xft_memset_512_streaming(t_any restrict dest,
					const t_u8 c, t_size n)\
					__attribute__((__nonnull__(1)));

void			xft_memcpy_512_streaming(t_any __restrict__ dest,\
					t_cany __restrict__ const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

#endif
