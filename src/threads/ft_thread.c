/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 23:40:17 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 11:33:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"
#include "mem.h"
#include "private/ft_p_syscalls.h"
#include "rt.h"
#include "syscalls.h"
#include "threads.h"
#include "private/ft_p_rt.h"
#include "private/ft_p_thread.h"

__attribute__((__nonnull__(1), pure))
t_thread_offset	ft__map_bytes(const t_xft_rt *__restrict__ const rt_info,
	const t_size stack_size)
{
	t_thread_offset		offsets;
	t_size				bytes;

	bytes = rt_info->elf.page_size;
	offsets.guard_offset = bytes;
	bytes += ft_max_s(rt_info->elf.page_size, stack_size);
	bytes = ft_align_fwd_integer(bytes, rt_info->elf.page_size);
	offsets.stack_offset = bytes;
	bytes = ft_align_fwd_integer(bytes, rt_info->elf.align);
	offsets.tls_offset = bytes;
	bytes += rt_info->elf.memsz + ft_align_fwd_integer(sizeof(t_uptr) << 1,
			rt_info->elf.align);
	bytes = ft_align_fwd_integer(bytes, _Alignof(t_thread_instance));
	offsets.instance_offset = bytes;
	bytes += sizeof(t_thread_instance);
	bytes = ft_align_fwd_integer(bytes, rt_info->elf.page_size);
	offsets.total_map = bytes;
	return (offsets);
}

__attribute__((__always_inline__, unused, __nonnull__(1)))
inline t_size	ft__tls_prep(const t_xft_rt *__restrict__ const rt_info,
	t_buffer area)
{
	t_uptr		tp;
	t_any		block;

	if (area.mem == nullptr)
		__builtin_unreachable();
	ft_memset(area.mem, 0, area.size);
	tp = (t_uptr)area.mem + ft__tcb_offset(rt_info);
	block = (t_any)((t_uptr)area.mem + ft__block_offset(rt_info));
	ft_memcpy(block, (t_any)rt_info->elf.vaddr, rt_info->elf.filesz);
	ft__write_abi_tcb(tp);
	return (tp);
}

__attribute__((__nonnull__(1, 2, 3)))
t_result	ft_thread_spawn(const t_xft_rt *__restrict__ const rt_info,
	t_thread *__restrict__ const thread,
	t_thread_arg *__restrict__ const arg, t_size stack_size)
{
	t_thread_offset					o;
	t_u8 *__restrict__				map;
	t_uptr							tp;
	t_buffer						area;
	t_thread_instance *__restrict__	inst;

	o = ft__map_bytes(rt_info, stack_size);
	map = ft_mmap(o.total_map, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS);
	if (__builtin_expect(ft_map_failed(map), 0))
		return (KO);
	if (__builtin_expect(ft_mprotect(map + o.guard_offset,
				o.total_map - o.guard_offset, PROT_READ | PROT_WRITE) == -1, 0))
		return (ft_munmap(map, o.total_map), KO);
	area = ft_fatptr(map + o.tls_offset, o.instance_offset - o.tls_offset);
	tp = ft__tls_prep(rt_info, area);
	inst = (t_thread_instance *)(map + o.instance_offset);
	inst->arg = *arg;
	inst->completion = (t_thread_completion){
		.completion = RUNNING, .mapped = ft_fatptr(map, o.total_map),
		.child_tid = 0, .parent_tid = 0};
	thread->completion = &inst->completion;
	return (ft__thread_clone(thread, o, tp, inst));
}
