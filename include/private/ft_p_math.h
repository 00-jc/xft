/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_math.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_MATH_H
# define FT_P_MATH_H

# include "math.h"

/*
 *	These are for multi-lane operations that map to SIMD registers.
 *	They shall NOT be passed as arguments to anything not protected
 *	by an ifdef, they should be used only inside scoped funcions.
 *	
 *	If not followed, the compiler will fail due to ABI boundary
 *	errors.
 *
 *	t_vu* types are an exception to this rule bc the scanning algorithms
 *	they perform are much more complex and they are protected by compile-time
 *	conditionals.
 *
 * 	To read arbitrary data from them use t_blk* from include/private/ft_p_asm.h.
 */

typedef __attribute__((vector_size(16), aligned(16), __may_alias__)) t_f64\
																	t_v2da;

typedef __attribute__((vector_size(16), aligned(16), __may_alias__)) t_u64a\
																	t_v2u64a;

typedef __attribute__((vector_size(32), aligned(32), __may_alias__)) t_f64\
																	t_v4da;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_f64\
																	t_v4d;

typedef __attribute__((vector_size(32), aligned(32), __may_alias__)) t_u64a\
																	t_v4u64a;

typedef __attribute__((vector_size(64), aligned(64), __may_alias__)) t_f64\
																	t_v8da;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) t_f64\
																	t_v8d;

typedef __attribute__((vector_size(64), aligned(64), __may_alias__)) t_u64a\
																	t_v8u64a;

typedef union u_v2di
{
	t_v2u64a	i;
	t_v2da		d;
}	t_v2di;

typedef union u_v4di
{
	t_v4u64a	i;
	t_v4da		d;
}	t_v4di;

typedef union u_v8di
{
	t_v8u64a	i;
	t_v8da		d;
}	t_v8di;

#endif
