/* ************************************************************************** */
/*                                                                            */
/*                                                      :::      ::::::::     */
/*   xft_p_vmanip_types.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 11:36:24 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/07 11:36:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_VMANIP_TYPES_H
# define XFT_P_VMANIP_TYPES_H

# include <xft/xft_p_asm.h>

typedef long long													t_llong;

// one bit per lane, bit-castable to the matching mask integer
typedef bool __attribute__((ext_vector_type(2)))					t_vb2;
typedef bool __attribute__((ext_vector_type(4)))					t_vb4;
typedef bool __attribute__((ext_vector_type(8)))					t_vb8;
typedef bool __attribute__((ext_vector_type(16)))					t_vb16;
typedef bool __attribute__((ext_vector_type(32)))					t_vb32;
typedef bool __attribute__((ext_vector_type(64)))					t_vb64;

# if defined(__GNUC__) && !defined(__clang__)

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) char\
																	t_vc128;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) char\
																	t_vc256;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) char\
																	t_vc512;

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_i16\
																	t_vs16_128;

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_i32\
																	t_vs32_128;

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_llong\
																	t_vs64_128;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_i16\
																	t_vs16_256;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_i32\
																	t_vs32_256;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_llong\
																	t_vs64_256;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_i16\
																	t_vs16_512;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_i32\
																	t_vs32_512;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_llong\
																	t_vs64_512;

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_f32\
																	t_vf32_128;

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_f64\
																	t_vf64_128;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_f32\
																	t_vf32_256;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_f64\
																	t_vf64_256;

# else

typedef t_vu16_128													t_vs16_128;
typedef t_vu32_128													t_vs32_128;
typedef t_vu64_128													t_vs64_128;
typedef t_vu16_256													t_vs16_256;
typedef t_vu32_256													t_vs32_256;
typedef t_vu64_256													t_vs64_256;
typedef t_vu16_512													t_vs16_512;
typedef t_vu32_512													t_vs32_512;
typedef t_vu64_512													t_vs64_512;

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_f32\
																	t_vf32_128;

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) t_f64\
																	t_vf64_128;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_f32\
																	t_vf32_256;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_f64\
																	t_vf64_256;

typedef t_vu128														t_vc128;
typedef t_vu256														t_vc256;
typedef t_vu512														t_vc512;

# endif

#endif
