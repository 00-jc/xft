/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_thread_spawn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 11:30:57 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 12:14:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(__linux__) && !defined(XFT_REQUIRE_LIBC)
# include <xft/threads.h>
# include <xft/xft_p_threads.h>
# include <xft/xft_p_syscalls.h>
# include <xft/rt.h>
# include <xft/xft_p_rt.h>
# include <xft/mem.h>
# include <xft/bmi.h>

__attribute__((__flatten__, __always_inline__, pure))
inline t_ts_offsets	xft__thread_layout(t_sysinfo sysinfo, t_thread_opts opts)
{
	t_ts_offsets	offsets;

	offsets.bytes = sysinfo.page_size;
	offsets.guard_offset = offsets.bytes;
	offsets.bytes += xft_max_s(sysinfo.page_size, opts.stack_size);
	offsets.bytes = (t_size)xft_align_fwd_integer(offsets.bytes,
			sysinfo.page_size);
	offsets.stack_offset = offsets.bytes;
	offsets.bytes = (t_size)xft_align_fwd_integer(offsets.bytes,
			sysinfo._linux.tls_align);
	offsets.tls_offset = offsets.bytes;
	offsets.bytes += sysinfo._linux.tls_size;
	offsets.bytes = (t_size)xft_align_fwd_integer(offsets.bytes,
			__alignof(t_thread_instance));
	offsets.instance_offset = offsets.bytes;
	offsets.bytes += sizeof(t_thread_instance);
	offsets.bytes = (t_size)xft_align_fwd_integer(offsets.bytes,
			sysinfo.page_size);
	return (offsets);
}

__attribute__((__nonnull__(1)))
static t_i32	xft__thread_entry(t_any arg)
{
	t_thread_instance *__restrict__ const	instance = arg;

	instance->fn(instance->argument);
	if (__atomic_exchange_n(&instance->status, THREAD_COMPLETED,
			xft_acq_rel) == THREAD_DETACHED)
		xft_thread_destroy(instance);
	return (0);
}

__attribute__((__always_inline__, __nonnull__(1, 2, 3, 4)))
static inline t_i32	xft__thread_clone(t_u8 *__restrict__ const map,
	const t_ts_offsets *__restrict__ const offsets,
	const t_sysinfo_linux *__restrict__ const l,
	t_thread_instance *__restrict__ const instance)
{
	t_clone_arg	args;

	args.flags = xft_clone_vm | xft_clone_fs | xft_clone_files
		| xft_clone_sighand | xft_clone_thread | xft_clone_sysvsem
		| xft_clone_settls | xft_clone_parent_settid
		| xft_clone_child_cleartid;
	args.stack = map + offsets->stack_offset;
	args.ptid = (t_i32a *)&instance->tid;
	args.ctid = args.ptid;
	args.tls = xft_tls_fill(map + offsets->tls_offset, l);
	args.fn = xft__thread_entry;
	args.arg = instance;
	return (xft_clone(&args));
}

__attribute__((__always_inline__, __nonnull__(1, 2)))
static inline t_result	xft__thread_guard(t_u8 *__restrict__ const map,
	const t_ts_offsets *__restrict__ const offsets)
{
	t_result	res;

	res = (t_result){.err = xft_err_retry};
	while (xft_should_retry(res))
		res = xft_mprotect(map + offsets->guard_offset,
				offsets->bytes - offsets->guard_offset,
				xft_prot_read | xft_prot_write);
	return (res);
}

__attribute__((__flatten__, __nonnull__(1)))
t_result	xft_thread_spawn(t_thread *__restrict__ const thread,
	t_sysinfo sysinfo, t_thread_opts opts)
{
	t_u8				*map;
	t_thread_instance	*instance;
	const t_ts_offsets	offsets = xft__thread_layout(sysinfo, opts);
	t_result			res;
	t_i32				tid;

	map = xft_mmap(offsets.bytes,
			xft_prot_none, xft_map_private | xft_map_anonymous);
	if (__builtin_expect(xft_map_failed(map).ok, 0))
		return ((t_result){.ok = KO, .err = -(t_uptr)map});
	res = xft__thread_guard(map, &offsets);
	if (__builtin_expect(!res.ok, 0))
		return ((void)(xft_munmap(map, offsets.bytes)), res);
	instance = (t_thread_instance *)(map + offsets.instance_offset);
	*instance = (t_thread_instance){.size = offsets.bytes, .fn = opts.fn,
		.argument = opts.argument, .status = THREAD_RUNNING, .base = map};
	tid = xft__thread_clone(map, &offsets, &sysinfo._linux, instance);
	if (__builtin_expect(tid < 0, 0))
		return ((void)(xft_munmap(map, offsets.bytes)),
			(t_result){.ok = KO, .err = -(t_u64a)tid});
	thread->instance = instance;
	return ((t_result){.ok = OK});
}

#endif
