/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:02:58 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 16:43:58 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMI_H
# define BMI_H

# include "private/ft_p_asm.h"
# include "types.h"

t_u64			__hasz64(t_u64 x)\
					__attribute__((const));
t_u64			__populate(t_u8 y)\
					__attribute__((const));

size_t			ft_memctz_u16(t_u16 x)\
					__attribute__((const));
size_t			ft_memctz_u32(t_u32 x)\
					__attribute__((const));
size_t			ft_memctz_u64(t_u64 x)\
					__attribute__((const));
size_t			ft_memctz_u128(t_u128 x)\
					__attribute__((const));

size_t			ft_memclz_u16(t_u16 x)\
					__attribute__((const));
size_t			ft_memclz_u32(t_u32 x)\
					__attribute__((const));
size_t			ft_memclz_u64(t_u64 x)\
					__attribute__((const));
size_t			ft_memclz_u128(t_u128 x)\
					__attribute__((const));

size_t			__max_s(size_t x, size_t y)\
					__attribute__((const));
t_u8			__maxu8(t_u8 x, t_u8 y)\
					__attribute__((const));
t_u32			__maxu32(t_u32 x, t_u32 y)\
					__attribute__((const));
t_u64			__maxu64(t_u64 x, t_u64 y)\
					__attribute__((const));
t_u128			__maxu128(t_u128 x, t_u128 y)\
					__attribute__((const));

t_u16a			ft_bswap16(t_u16a x)\
					__attribute__((const));
t_u32a			ft_bswap32(t_u32a x)\
					__attribute__((const));
t_u64a			ft_bswap64(t_u64a x)\
					__attribute__((const));

t_u16a			ft_to_be16(t_u16a x)\
					__attribute__((const));
t_u32a			ft_to_be32(t_u32a x)\
					__attribute__((const));
t_u64a			ft_to_be64(t_u64a x)\
					__attribute__((const));
size_t			ft_roll_mask(size_t chunk_size, size_t n)\
					__attribute__((const));
t_u64a			ft_rotl64(t_u64a hash, size_t n)\
					__attribute__((const));

t_u64a			ft_tern(t_u64a cond, t_u64a value1,\
					t_u64a value2)\
					__attribute__((const));

t_f64			ft_dtern(t_u64a cond, t_f64 value1,\
					t_f64 value2)\
					__attribute__((const));

size_t			ft_next_pow2(size_t qword)\
					__attribute__((const));

#endif
