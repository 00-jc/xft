/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmi.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/14 02:14:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMI_H
# define BMI_H

# include "xft_p_asm.h"
# include "primitives.h"

t_u64			xft_hasz64(t_u64 x)\
					__attribute__((const));
t_u64			xft_populate(t_u8 y)\
					__attribute__((const));

t_u32a			xft_popcount_u32(t_u32a x)\
					__attribute__((const));
t_u64a			xft_popcount_u64(t_u64a x)\
					__attribute__((const));

t_size			xft_memctz_u16(t_u16 x)\
					__attribute__((const));
t_size			xft_memctz_u32(t_u32 x)\
					__attribute__((const));
t_size			xft_memctz_u64(t_u64 x)\
					__attribute__((const));
t_size			xft_memctz_u128(t_u128 x)\
					__attribute__((const));

t_size			xft_memclz_u16(t_u16 x)\
					__attribute__((const));
t_size			xft_memclz_u32(t_u32 x)\
					__attribute__((const));
t_size			xft_memclz_u64(t_u64 x)\
					__attribute__((const));
t_size			xft_memclz_u128(t_u128 x)\
					__attribute__((const));

t_size			xft_max_s(t_size x, t_size y)\
					__attribute__((const));
t_u8			xft_maxu8(t_u8 x, t_u8 y)\
					__attribute__((const));
t_u32			xft_maxu32(t_u32 x, t_u32 y)\
					__attribute__((const));
t_u64			xft_maxu64(t_u64 x, t_u64 y)\
					__attribute__((const));
t_u128			xft_maxu128(t_u128 x, t_u128 y)\
					__attribute__((const));

t_u16a			xft_bswap16(t_u16a x)\
					__attribute__((const));
t_u32a			xft_bswap32(t_u32a x)\
					__attribute__((const));
t_u64a			xft_bswap64(t_u64a x)\
					__attribute__((const));

t_u16a			xft_to_be16(t_u16a x)\
					__attribute__((const));
t_u32a			xft_to_be32(t_u32a x)\
					__attribute__((const));
t_u64a			xft_to_be64(t_u64a x)\
					__attribute__((const));
t_size			xft_roll_mask(t_size chunk_size, t_size n)\
					__attribute__((const));
t_u64a			xft_rotl64(t_u64a hash, t_size n)\
					__attribute__((const));

t_u64a			xft_tern(t_u64a cond, t_u64a value1,\
					t_u64a value2)\
					__attribute__((const));

t_f64			xft_dtern(t_u64a cond, t_f64 value1,\
					t_f64 value2)\
					__attribute__((const));

t_size			xft_next_pow2(t_size qword)\
					__attribute__((const, __hot__));

t_size			xft_last_pow2(t_size qword)\
					__attribute__((const, __hot__));

t_u64			xft_align_fwd_integer(t_u64a n, t_u64 align)\
					__attribute__((const, __hot__));

t_u64			xft_align_bwd_integer(t_u64a n, t_u64 align)\
					__attribute__((const, __hot__));

#endif
