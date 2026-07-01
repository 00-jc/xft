/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include "primitives.h"
# include "bmi.h"

# define LONES_64 			0x0101010101010101ULL
# define HIGHS_64	 		0x8080808080808080ULL

void			ft_bzero(void *__restrict__ ptr, t_size n)\
					__attribute__((__nonnull__(1)));

void			ft_memset(void *__restrict__ s, const t_u8 c, t_size n)\
					__attribute__((__nonnull__(1)));

void			ft_memcpy(void *__restrict__ dest,
					const void *__restrict__ src, t_size n)\
					__attribute__((__nonnull__(1, 2), __hot__));

void			ft_memtake(void *__restrict__ dest,
					void *__restrict__ src, t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_memmove(void *__restrict__ dest,
					const void *__restrict__ src, t_size n)\
					__attribute__((__nonnull__(1, 2), __hot__));

void			*ft_memchr(const void *__restrict__ ptr, int c, t_size n)\
					__attribute__((__nonnull__(1)));

t_ssize			ft_memcmp(const void *__restrict__ const dest,
					const void *__restrict__ src, t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_membroadcast(void *dst, void *src, t_size chunks, t_size n)\
					__attribute__((__nonnull__(1, 2)));

void			ft_prefetch0(const void *__restrict__ const ptr, t_size size)\
					__attribute__((__nonnull__(1)));

void			ft_prefetch1(const void *__restrict__ const ptr, t_size size)\
					__attribute__((__nonnull__(1)));

void			ft_prefetch2(const void *__restrict__ const ptr, t_size size)\
					__attribute__((__nonnull__(1)));

void			ft_prefetchnta(const void *__restrict__ const ptr, t_size size)\
					__attribute__((__nonnull__(1)));

void			*ft_overlap(const void *__restrict__ ptr,\
					t_size chunk_size, t_size rem_size)\
					__attribute__((__nonnull__(1), const));

t_buffer		ft_fatptr(t_blk8r mem, t_size size)\
					__attribute__((const));

void			*ft_align_fwd(void *ptr, const t_size align)\
					__attribute__((const, __nonnull__(1),\
					__returns_nonnull__));

void			*ft_align_bkw(void *ptr, const t_size align)\
					__attribute__((const, __nonnull__(1),\
					__returns_nonnull__));

void			ft_stfence(void);
void			ft_ldfence(void);

#endif
