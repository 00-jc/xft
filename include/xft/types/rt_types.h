/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/22 04:10:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPES_H
# define RT_TYPES_H

# include <xft/types/elf_types.h>
# include <xft/types/x86_64_types.h>

typedef t_u8										t_nat_str;

typedef const t_nat_str *__restrict__ *__restrict__	t_rt_arr;

# if defined(_WIN32)

typedef struct s_kernel_ptrs
{
	t_size											argc;
	t_rt_arr										argv;
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

typedef struct s_xft_arch
{
	bool												has_128_vec;
	bool												has_256_vec;
	bool												has_512_vec;
	t_x86_ver											x86_64_ver;
}	t_xft_arch;

#endif
