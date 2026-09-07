/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_thread_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:22:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 11:37:33 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_rt.h"
#include "mem.h"
#include "elf.h"
#include "bmi.h"

#ifndef FT_NO_RT

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft__get_thread_info(t_xft_rt *__restrict__ const rt)
{
	t_size		i;

	i = 0;
	rt->elf.load_bias = 0;
	while (i < rt->phdr.phnum)
	{
		if (rt->phdr.phdr[i].p_type == PT_TLS)
		{
			rt->elf.filesz = rt->phdr.phdr[i].p_filesz;
			rt->elf.memsz = rt->phdr.phdr[i].p_memsz;
			rt->elf.align = rt->phdr.phdr[i].p_align;
			rt->elf.vaddr = rt->phdr.phdr[i].p_vaddr;
		}
		else if (rt->phdr.phdr[i].p_type == PT_PHDR)
			rt->elf.load_bias = (t_uptr)rt->phdr.phdr
				- rt->phdr.phdr[i].p_vaddr;
		++i;
	}
	rt->elf.align = ft_tern(rt->elf.align < sizeof(t_uptr), sizeof(t_uptr),
			rt->elf.align);
	rt->elf.vaddr += rt->elf.load_bias;
	rt->elf.memsz = ft_align_fwd_integer(rt->elf.memsz, rt->elf.align);
}

#endif
