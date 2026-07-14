/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_mem.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 22:31:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_MEM_H
# define FT_P_MEM_H

# include "mem.h"
# include "private/ft_p_bmi.h"

# ifndef FT_LLC_SIZE
#  define FT_LLC_SIZE 16777216ULL
# endif

typedef struct s_t_f64_size
{
	t_size		i;
	t_size		blks;
}	t_t_f64_size;

void			ft_memcpy_naive(t_any __restrict__ dest,
					t_cany __restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memcpy_512_huge(t_any __restrict__ dest,\
					t_cany __restrict__ const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memmove_512_huge(t_any __restrict__ dest,\
					t_cany __restrict__ const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memcpy_64(t_any __restrict__ dest,
					t_cany __restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memset_naive(t_any __restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));
void			ft_memset_64(t_any __restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			ft_memcpy_128(t_any __restrict__ dest,
					t_cany __restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));
void			ft_memcpy_256(t_any __restrict__ dest,
					t_cany __restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));
void			ft_memcpy_512(t_any __restrict__ dest,
					t_cany __restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_movsb(t_any __restrict__ dest,
					t_cany __restrict__ src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_movsq(t_any __restrict__ dest,
					t_cany __restrict__ src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memset_128(t_any __restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			ft_memset_256(t_any __restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			ft_memset_512(t_any __restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			ft_memset_512_huge(t_any __restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

t_any			ft_memchr_minimal(t_cany ptr,
					t_u8 c, t_size n)\
					__attribute__((__nonnull__(1)));

t_any			ft_memchr_128(t_cany ptr,\
					int c, t_size n)\
					__attribute__((__nonnull__(1)));

t_any			ft_memchr_256(t_cany ptr,
					int c, t_size n)\
					__attribute__((__nonnull__(1)));

t_any			ft_memchr_512(t_cany ptr,
					int c, t_size n)\
					__attribute__((__nonnull__(1)));

t_ssize			ft_memcmp_minimal(t_cany __restrict__ const ptr1,
					t_cany __restrict__ const ptr2, t_size offst,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

t_ssize			ft_memcmp_128(t_cany __restrict__ const ptr1,
					t_cany __restrict__ const ptr2, t_size n)\
					__attribute__((__nonnull__(1, 2)));

t_ssize			ft_memcmp_256(t_cany __restrict__ const ptr1,
					t_cany __restrict__ const ptr2, t_size n)\
					__attribute__((__nonnull__(1, 2)));

t_ssize			ft_memcmp_512(t_cany __restrict__ const ptr1,
					t_cany __restrict__ const ptr2, t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memset_512_streaming(t_any restrict dest,
					const t_u8 c, t_size n)\
					__attribute__((__nonnull__(1)));

void			ft_memcpy_512_streaming(t_any __restrict__ dest,\
					t_cany __restrict__ const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

#endif
