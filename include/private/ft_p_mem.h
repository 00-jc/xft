/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_mem.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:23:58 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 22:56:09 by jaicastr         ###   ########.fr       */
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

void			ft_memcpy_naive(void *__restrict__ dest,
					const void	*__restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memcpy_512_huge(void *__restrict__ dest,\
					const void	*__restrict__ const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memmove_512_huge(void *__restrict__ dest,\
					const void	*__restrict__ const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memcpy_64(void *__restrict__ dest,
					const void	*__restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memset_naive(void *__restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));
void			ft_memset_64(void *__restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			ft_memcpy_128(void *__restrict__ dest,
					const void	*__restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));
void			ft_memcpy_256(void *__restrict__ dest,
					const void	*__restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));
void			ft_memcpy_512(void *__restrict__ dest,
					const void	*__restrict__ const src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_movsb(void *__restrict__ dest,
					const void	*__restrict__ src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_movsq(void *__restrict__ dest,
					const void	*__restrict__ src,
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memset_128(void *__restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			ft_memset_256(void *__restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			ft_memset_512(void *__restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			ft_memset_512_huge(void *__restrict__ dest,
					const t_u8 b, t_size n)\
					__attribute__((__nonnull__(1)));

void			*ft_memchr_minimal(const void *ptr,
					t_u8 c, t_size n)\
					__attribute__((__nonnull__(1)));

void			*ft_memchr_sse(const void *ptr,
					int c, t_size n)\
					__attribute__((__nonnull__(1)));

void			*ft_memchr_avx256(const void *ptr,
					int c, t_size n)\
					__attribute__((__nonnull__(1)));

void			*ft_memchr_avx512(const void *ptr,
					int c, t_size n)\
					__attribute__((__nonnull__(1)));

t_ssize			ft_memcmp_minimal(const void *__restrict__ const ptr1,
					const void	*__restrict__ const ptr2, t_size offst,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

t_ssize			ft_memcmp_sse(const void *__restrict__ const ptr1,
					const void	*__restrict__ const ptr2, t_size n)\
					__attribute__((__nonnull__(1, 2)));

t_ssize			ft_memcmp_avx256(const void *__restrict__ const ptr1,
					const void	*__restrict__ const ptr2, t_size n)\
					__attribute__((__nonnull__(1, 2)));

t_ssize			ft_memcmp_avx512(const void *__restrict__ const ptr1,
					const void	*__restrict__ const ptr2, t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memset_512_streaming(void *restrict dest,
					const t_u8 c, t_size n)\
					__attribute__((__nonnull__(1)));

void			ft_memcpy_512_streaming(void *__restrict__ dest,\
					const void	*__restrict__ const src,\
					t_size n)\
					__attribute__((__nonnull__(1, 2)));

#endif
