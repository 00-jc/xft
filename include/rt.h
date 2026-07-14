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

typedef struct s_elf64_auxv
{
	t_u64			a_type;
	t_u64			a_val;
}	t_elf64_auxv;

typedef const t_elf64_auxv *__restrict__				t_auxv;

# ifdef __clang__

typedef struct s_kernel_ptrs
{
	t_size											argc;
	t_rt_arr __attribute__	((counted_by(argc)))	argv;
	t_size											envc;
	t_rt_arr __attribute__	((counted_by(envc)))	envp;
	t_size											auxc;
	t_auxv __attribute__	((counted_by(auxc)))	auxv;
}	t_kernel_ptrs;

typedef struct s_phdr
{
	t_u64a															phnum;
	t_elf_phdr *__restrict__ __attribute__	((counted_by(phnum)))	phdr;
	t_u64a															phent;
}	t_phdr;

typedef struct s_hwcaps
{
	t_u64a												hwcap;
	t_u64a												hwcap2;
}	t_hwcaps;

typedef struct s_elf_info
{
	t_u64a												load_bias;
	t_u64a												page_size;
	t_u64a												filesz;
	t_u64a												memsz;
	t_u64a												align;
	t_u64a												vaddr;
}	t_elf_info;

typedef struct s_xft_rt
{
	t_kernel_ptrs										kp;
	t_u64a												random;
	t_elf_info											elf;
	t_phdr												phdr;
}	t_xft_rt;

# else

typedef struct s_kernel_ptrs
{
	t_size											argc;
	t_rt_arr										argv;
	t_size											envc;
	t_rt_arr										envp;
	t_size											auxc;
	t_auxv											auxv;
}	t_kernel_ptrs;

typedef struct s_phdr
{
	t_u64a															phnum;
	t_elf_phdr *__restrict__ __attribute__	((counted_by(phnum)))	phdr;
	t_u64a															phent;
}	t_phdr;

typedef struct s_hwcaps
{
	t_u64a												hwcap;
	t_u64a												hwcap2;
}	t_hwcaps;

typedef struct s_elf_info
{
	t_u64a												load_bias;
	t_u64a												page_size;
	t_u64a												filesz;
	t_u64a												memsz;
	t_u64a												align;
	t_u64a												vaddr;
}	t_elf_info;

typedef struct s_xft_rt
{
	t_kernel_ptrs										kp;
	t_u64a												random;
	t_elf_info											elf;
	t_phdr												phdr;
}	t_xft_rt;

# endif

# if defined(__x86_64__) && !defined(FT_REQUIRE_LIBC)

void			_start(void)\
					__attribute__((noreturn, force_align_arg_pointer));

# elif defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)

void			_start(void)\
					__attribute__((noreturn));

# endif

void			ft_main(const t_any *__restrict__ const sp)\
					__attribute__((__nonnull__(1), used, noreturn));

t_kernel_ptrs	ft_get_kernel_ptrs(const t_any *sp)\
					__attribute__((__nonnull__(1)));

t_xft_rt		ft_get_rt(const t_any *sp)\
					__attribute__((__nonnull__(1)));

#endif
