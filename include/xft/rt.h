/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/22 04:10:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <xft/types/rt_types.h>

# ifndef XFT_NO_RT

#  if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

void			_start(void)\
					__attribute__((noreturn, force_align_arg_pointer));

#  elif !defined(XFT_REQUIRE_LIBC)

void			_start(void)\
					__attribute__((noreturn));

#  endif

void			xft_main(const t_any *__restrict__ const sp)\
					__attribute__((__nonnull__(1), used, noreturn));

# endif

t_kernel_ptrs	xft_get_kernel_ptrs(const t_any *sp)\
					__attribute__((__nonnull__(1)));

t_xft_rt		xft_get_rt(const t_any *sp)\
					__attribute__((__nonnull__(1)));

void			xft_kernel_ptrs_destroy(t_kernel_ptrs *kp)\
					__attribute__((__nonnull__(1)));

t_xft_arch		xft_dyn_cpu_select(void)\
					__attribute__((const));

void			xft_exit_process(t_i32a code)\
					__attribute__((__cold__, __noreturn__));

#endif
