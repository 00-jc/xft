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

# if defined(__GNUC__) && !defined(__clang__)

typedef __attribute__((vector_size(16), aligned(1), __may_alias__)) char\
																	t_vc128;

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) char\
																	t_vc256;

typedef __attribute__((vector_size(64), aligned(1), __may_alias__)) char\
																	t_vc512;

# else

typedef t_vu128														t_vc128;
typedef t_vu256														t_vc256;
typedef t_vu512														t_vc512;

# endif

#endif
