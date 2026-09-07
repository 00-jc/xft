/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_auxv_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:22:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_rt.h"
#include "elf.h"
#include "bmi.h"

#ifndef FT_NO_RT

__attribute__((__nonnull__(1, 2), __hot__, __always_inline__))
inline void	ft_get_auxv_size(t_xft_rt *__restrict__ const rt, t_auxv auxv)
{
	t_u64a	t;

	t = auxv->a_type;
	while (t != AT_NULL)
	{
		rt->elf.page_size = ft_tern(t == AT_PAGESZ, auxv->a_val,
				rt->elf.page_size);
		rt->random = ft_tern(t == AT_RANDOM, auxv->a_val, rt->random);
		rt->phdr.phdr = (t_any)ft_tern(t == AT_PHDR, auxv->a_val,
				(t_uptr)rt->phdr.phdr);
		rt->phdr.phnum = ft_tern(t == AT_PHNUM, auxv->a_val, rt->phdr.phnum);
		rt->phdr.phent = ft_tern(t == AT_PHENT, auxv->a_val, rt->phdr.phent);
		++auxv;
		t = auxv->a_type;
	}
	ft__get_thread_info(rt);
}

#endif
