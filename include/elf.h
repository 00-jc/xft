/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF_H
# define ELF_H

# include "primitives.h"

# define AT_NULL              0
# define AT_IGNORE            1
# define AT_EXECFD            2
# define AT_PHDR              3
# define AT_PHENT             4
# define AT_PHNUM             5
# define AT_PAGESZ            6
# define AT_BASE              7
# define AT_FLAGS             8
# define AT_ENTRY             9
# define AT_NOTELF           10
# define AT_UID              11
# define AT_EUID             12
# define AT_GID              13
# define AT_EGID             14
# define AT_PLATFORM         15
# define AT_HWCAP            16
# define AT_CLKTCK           17
# define AT_SECURE           23
# define AT_BASE_PLATFORM    24
# define AT_RANDOM           25
# define AT_HWCAP2           26
# define AT_EXECFN           31
# define AT_SYSINFO          32
# define AT_SYSINFO_EHDR     33

# define PT_PHDR	6
# define PT_TLS		7

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
