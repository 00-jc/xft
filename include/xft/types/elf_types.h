/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF_TYPES_H
# define ELF_TYPES_H

# include <xft/primitives.h>

typedef enum e_xft_auxv : t_u8
{
	XFT_AT_NULL = 0,
	XFT_AT_IGNORE = 1,
	XFT_AT_EXECFD = 2,
	XFT_AT_PHDR = 3,
	XFT_AT_PHENT = 4,
	XFT_AT_PHNUM = 5,
	XFT_AT_PAGESZ = 6,
	XFT_AT_BASE = 7,
	XFT_AT_FLAGS = 8,
	XFT_AT_ENTRY = 9,
	XFT_AT_NOTELF = 10,
	XFT_AT_UID = 11,
	XFT_AT_EUID = 12,
	XFT_AT_GID = 13,
	XFT_AT_EGID = 14,
	XFT_AT_PLATFORM = 15,
	XFT_AT_HWCAP = 16,
	XFT_AT_CLKTCK = 17,
	XFT_AT_SECURE = 23,
	XFT_AT_BASE_PLATFORM = 24,
	XFT_AT_RANDOM = 25,
	XFT_AT_HWCAP2 = 26,
	XFT_AT_EXECFN = 31,
	XFT_AT_SYSINFO = 32,
	XFT_AT_SYSINFO_EHDR = 33,
}	t_xft_auxv;

typedef enum e_xft_ptype : t_u8
{
	XFT_PT_PHDR = 6,
	XFT_PT_TLS = 7,
}	t_xft_ptype;

# if __SIZEOF_POINTER__ == 8

typedef struct s_elf_phdr
{
	t_u32	p_type;
	t_u32	p_flags;
	t_u64	p_offset;
	t_u64	p_vaddr;
	t_u64	p_paddr;
	t_u64	p_filesz;
	t_u64	p_memsz;
	t_u64	p_align;
} __attribute__((__aligned__(1), __may_alias__))	t_elf_phdr;

# elif __SIZEOF_POINTER__ == 4

typedef struct s_elf_phdr
{
	t_u32	p_type;
	t_u32	p_offset;
	t_u32	p_vaddr;
	t_u32	p_paddr;
	t_u32	p_filesz;
	t_u32	p_memsz;
	t_u32	p_flags;
	t_u32	p_align;
} __attribute__((__aligned__(1), __may_alias__))	t_elf_phdr;

# else

#  error "Cannot get a phdr for this"

# endif

#endif
