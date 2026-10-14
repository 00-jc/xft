/* ************************************************************************** */
/*                                                                            */
/*                                                      :::      ::::::::     */
/*   xft_p_vmanip.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 11:36:24 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/07 11:36:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_VMANIP_H
# define XFT_P_VMANIP_H

# include "xft_p_asm.h"

typedef long long													t_llong;

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
