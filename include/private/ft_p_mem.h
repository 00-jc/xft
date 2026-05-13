/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_mem.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:23:58 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 23:49:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_MEM_H
# define FT_P_MEM_H

# include "mem.h"
# include "private/ft_p_bmi.h"

typedef struct s_t_f64_size
{
	size_t		i;
	size_t		blks;
}	t_t_f64_size;

void			ft_memcpy_naive(void *__restrict__ dest,
					const void	*__restrict__ const src,
					size_t n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memcpy_512_huge(void *__restrict__ dest,\
					const void	*__restrict__ const src,\
					size_t n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memmove_512_huge(void *__restrict__ dest,\
					const void	*__restrict__ const src,\
					size_t n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memcpy_64(void *__restrict__ dest,
					const void	*__restrict__ const src,
					size_t n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memset_naive(void *__restrict__ dest,
					const t_u8 b, size_t n)\
					__attribute__((__nonnull__(1)));
void			ft_memset_64(void *__restrict__ dest,
					const t_u8 b, size_t n)\
					__attribute__((__nonnull__(1)));

void			ft_memcpy_128(void *__restrict__ dest,
					const void	*__restrict__ const src,
					size_t n)\
					__attribute__((__nonnull__(1, 2)));
void			ft_memcpy_256(void *__restrict__ dest,
					const void	*__restrict__ const src,
					size_t n)\
					__attribute__((__nonnull__(1, 2)));
void			ft_memcpy_512(void *__restrict__ dest,
					const void	*__restrict__ const src,
					size_t n)\
					__attribute__((__nonnull__(1, 2)));
void			ft_movsb(void *__restrict__ dest,
					const void	*__restrict__ const src,
					size_t n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memset_128(void *__restrict__ dest,
					const t_u8 b, size_t n)\
					__attribute__((__nonnull__(1)));

void			ft_memset_256(void *__restrict__ dest,
					const t_u8 b, size_t n)\
					__attribute__((__nonnull__(1)));

void			ft_memset_512(void *__restrict__ dest,
					const t_u8 b, size_t n)\
					__attribute__((__nonnull__(1)));

void			*ft_memchr_minimal(const void *ptr,
					t_u8 c, size_t n)\
					__attribute__((__nonnull__(1)));

void			*ft_memchr_sse(const void *ptr,
					int c, size_t n)\
					__attribute__((__nonnull__(1)));

void			*ft_memchr_avx256(const void *ptr,
					int c, size_t n)\
					__attribute__((__nonnull__(1)));

void			*ft_memchr_avx512(const void *ptr,
					int c, size_t n)\
					__attribute__((__nonnull__(1)));

ssize_t			ft_memcmp_minimal(const void *__restrict__ const ptr1,
					const void	*__restrict__ const ptr2, size_t offst,\
					size_t n)\
					__attribute__((__nonnull__(1, 2)));

ssize_t			ft_memcmp_sse(const void *__restrict__ const ptr1,
					const void	*__restrict__ const ptr2, size_t n)\
					__attribute__((__nonnull__(1, 2)));

ssize_t			ft_memcmp_avx256(const void *__restrict__ const ptr1,
					const void	*__restrict__ const ptr2, size_t n)\
					__attribute__((__nonnull__(1, 2)));

ssize_t			ft_memcmp_avx512(const void *__restrict__ const ptr1,
					const void	*__restrict__ const ptr2, size_t n)\
					__attribute__((__nonnull__(1, 2)));

#endif
