/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 11:31:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "syscalls.h"
# include "elf.h"

# ifdef _WIN64

typedef t_u16										t_nat_str;

# else

typedef t_u8										t_nat_str;

# endif

typedef const t_nat_str *__restrict__ *__restrict__	t_rt_arr;

# if defined(_WIN64)

typedef struct s_kernel_ptrs
{
	t_size											argc;
	const t_nat_str *const *__restrict__			argv;
	const t_nat_str *__restrict__					envp;
}	t_kernel_ptrs;

# elif defined(__clang__)

typedef struct s_kernel_ptrs
{
	t_size											argc;
	t_rt_arr __attribute__	((counted_by(argc)))	argv;
	t_rt_arr										envp;
}	t_kernel_ptrs;

# else

typedef struct s_kernel_ptrs
{
	t_size											argc;
	t_rt_arr										argv;
	t_rt_arr										envp;
}	t_kernel_ptrs;

# endif

typedef struct s_hwcaps
{
	t_u64a												hwcap;
	t_u64a												hwcap2;
}	t_hwcaps;

typedef struct s_xft_rt
{
	t_kernel_ptrs										kp;
}	t_xft_rt;

# ifndef XFT_NO_RT

#  if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

void			_start(void)\
					__attribute__((noreturn, force_align_arg_pointer));

#  elif defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

void			_start(void)\
					__attribute__((noreturn));

#  endif

void			xft_main(const t_any *__restrict__ const sp)\
					__attribute__((__nonnull__(1), used, noreturn));

t_kernel_ptrs	xft_get_kernel_ptrs(const t_any *sp)\
					__attribute__((__nonnull__(1)));

t_xft_rt		xft_get_rt(const t_any *sp)\
					__attribute__((__nonnull__(1)));

#  if defined(_WIN64)

/* argv (LocalFree) and envp (FreeEnvironmentStringsW) come from the system */
void			xft_free_kernel_ptrs(t_kernel_ptrs *kp)\
					__attribute__((__nonnull__(1)));

#  endif

# endif

#endif
