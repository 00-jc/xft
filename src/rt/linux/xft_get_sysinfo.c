/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_sysinfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 21:43:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/28 21:59:59 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/rt.h>
#include <xft/xft_p_rt.h>
#include <xft/bmi.h>
#include <xft/os.h>
#include <xft/xft_p_syscalls.h>

__attribute__((__always_inline__, __nonnull__(1, 2)))
static inline void	xft_sysinfo_auxv(t_sysinfo *__restrict__ const info,
	const t_auxval_linux *__restrict__ const aux)
{
	const t_size	t = aux->a_type;
	const t_size	v = aux->a_val;

	info->random = (t_any)xft_tern_s(t == XFT_AT_RANDOM, v,
			(t_uptr)info->random);
	info->page_size = xft_tern_s(t == XFT_AT_PAGESZ, v, info->page_size);
	info->_linux.vdso = (t_any)xft_tern_s(t == XFT_AT_SYSINFO_EHDR, v,
			(t_uptr)info->_linux.vdso);
	info->_linux.phdr = (t_any)xft_tern_s(t == XFT_AT_PHDR, v,
			(t_uptr)info->_linux.phdr);
	info->_linux.phnum = xft_tern_s(t == XFT_AT_PHNUM, v, info->_linux.phnum);
	info->_linux.sigstack_size = xft_tern_s(t == XFT_AT_MINSIGSTKSZ, v,
			info->_linux.sigstack_size);
	info->_linux.secure = xft_tern_s(t == XFT_AT_SECURE, v,
			info->_linux.secure);
	info->cache_line_size = (t_u32a)xft_tern_s(t == XFT_AT_L1D_CACHEGEOMETRY,
			v & 0xffff, info->cache_line_size);
}

__attribute__((__always_inline__, __nonnull__(1)))
static inline void	xft_sysinfo_tls(t_sysinfo *__restrict__ const info)
{
	const t_elf_phdr *__restrict__ const	ph = info->_linux.phdr;
	const t_elf_phdr						*tls;
	t_size									bias;
	t_size									i;

	tls = nullptr;
	bias = 0;
	i = 0;
	while (i < info->_linux.phnum)
	{
		bias = xft_tern_s(ph[i].p_type == XFT_PT_PHDR,
				(t_uptr)ph - ph[i].p_vaddr, bias);
		tls = (t_any)xft_tern_s(ph[i].p_type == XFT_PT_TLS,
				(t_uptr)(ph + i), (t_uptr)tls);
		++i;
	}
	if (tls == nullptr)
		return ;
	info->_linux.tls_image = (t_any)(tls->p_vaddr + bias);
	info->_linux.tls_filesz = tls->p_filesz;
	info->_linux.tls_memsz = tls->p_memsz;
	info->_linux.tls_align = tls->p_align;
}

__attribute__((__nonnull__(1), __always_inline__, __used__, pure, __flatten__))
inline t_sysinfo	xft_get_sysinfo(const t_any *__restrict__ sp)
{
	const t_auxval_linux *__restrict__	aux;
	t_sysinfo							info;
	t_size								cpus;
	t_result							res;
	t_rlimit							lim;

	sp += ((const t_size *)sp)[0] + 2;
	while (*sp)
		++sp;
	aux = (const t_auxval_linux *)(sp + 1);
	info = (t_sysinfo){};
	while (aux->a_type != XFT_AT_NULL)
		xft_sysinfo_auxv(&info, aux++);
	xft_sysinfo_tls(&info);
	lim = (t_rlimit){};
	xft_prlimit64(0, xft_rlimit_stack, nullptr, &lim);
	info.stack_size = (t_size)lim.rlim_cur;
	res = xft_get_cpu_count(&cpus);
	info.cpu_count = (t_u32a)xft_tern(res == OK, cpus, 1);
	info.cache_line_size = (t_u32a)xft_tern_s(info.cache_line_size == 0,
			xft_cache_line_size(), info.cache_line_size);
	return (info);
}
