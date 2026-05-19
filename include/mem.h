/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:14:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 02:03:56 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# ifdef __cplusplus

extern "C"
{

# endif

# include <sys/types.h>
# include <stdlib.h>
# include <limits.h>
# include "types.h"
# include "bmi.h"

# define LONES_64 			0x0101010101010101ULL
# define HIGHS_64	 		0x8080808080808080ULL

void			ft_bzero(void *__restrict__ ptr, size_t n)\
					__attribute__((__nonnull__(1)));

void			ft_memset(void *__restrict__ s, const t_u8 c, size_t n)\
					__attribute__((__nonnull__(1)));

void			ft_memcpy(void *__restrict__ dest,
					const void *__restrict__ src, size_t n)\
					__attribute__((__nonnull__(1, 2), __hot__));

void			ft_memtake(void *__restrict__ dest,
					void *__restrict__ src, size_t n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memmove(void *__restrict__ dest,
					const void *__restrict__ src, size_t n)\
					__attribute__((__nonnull__(1, 2), __hot__));

void			*ft_memchr(const void *__restrict__ ptr, int c, size_t n)\
					__attribute__((__nonnull__(1)));

ssize_t			ft_memcmp(const void *__restrict__ const dest,
					const void *__restrict__ src, size_t n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_membroadcast(void *dst, void *src, size_t chunks, size_t n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_prefetch0(const void *__restrict__ const ptr, size_t size)\
					__attribute__((__nonnull__(1)));

void			ft_prefetch1(const void *__restrict__ const ptr, size_t size)\
					__attribute__((__nonnull__(1)));

void			ft_prefetch2(const void *__restrict__ const ptr, size_t size)\
					__attribute__((__nonnull__(1)));

void			ft_prefetchnta(const void *__restrict__ const ptr, size_t size)\
					__attribute__((__nonnull__(1)));

void			*ft_overlap(const void *__restrict__ ptr,\
					size_t chunk_size, size_t rem_size)\
					__attribute__((__nonnull__(1), const));

t_buffer		ft_fatptr(t_blk8r mem, size_t size)\
					__attribute__((const));

void			*ft_align_fwd(void *ptr, const size_t align)\
					__attribute__((const, __nonnull__(1),\
					__returns_nonnull__));

void			*ft_align_bkw(void *ptr, const size_t align)\
					__attribute__((const, __nonnull__(1),\
					__returns_nonnull__));

void			ft_fence(void);

# ifdef __cplusplus
}
# endif

#endif
