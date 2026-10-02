/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 00:49:26 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINUX_H
# define LINUX_H

# ifdef __linux__
#  include "primitives.h"

#  ifdef XFT_REQUIRE_LIBC

#   include <linux/perf_event.h>

typedef struct perf_event_attr	t_perf_event_attr;

#  else

#   define PERF_TYPE_HARDWARE					0
#   define PERF_TYPE_SOFTWARE					1

#   define PERF_COUNT_HW_CPU_CYCLES				0
#   define PERF_COUNT_HW_INSTRUCTIONS			1
#   define PERF_COUNT_HW_CACHE_LL				2
#   define PERF_COUNT_HW_CACHE_MISSES			3
#   define PERF_COUNT_HW_BRANCH_INSTRUCTIONS	4
#   define PERF_COUNT_HW_BRANCH_MISSES			5

#   define PERF_COUNT_SW_PAGE_FAULTS			2
#   define PERF_COUNT_SW_ALIGNMENT_FAULTS		7
#   define PERF_COUNT_SW_DUMMY					9

#   define PERF_FORMAT_TOTAL_TIME_ENABLED		0x01U
#   define PERF_FORMAT_TOTAL_TIME_RUNNING		0x02U
#   define PERF_FORMAT_GROUP					0x08U

#   define PERF_FLAG_FD_CLOEXEC					0x08UL

#   define PERF_IOC_FLAG_GROUP					0x01
#   define PERF_EVENT_IOC_ENABLE				0x2400
#   define PERF_EVENT_IOC_DISABLE				0x2401
#   define PERF_EVENT_IOC_RESET					0x2403

typedef union u_linux_perf_period
{
	t_u64a	sample_period;
	t_u64a	sample_freq;
}	t_linux_perf_period;

typedef union u_linux_perf_wakeup
{
	t_u32a	wakeup_events;
	t_u32a	wakeup_watermark;
}	t_linux_perf_wakeup;

typedef union u_linux_perf_bp_addr
{
	t_u64a	bp_addr;
	t_u64a	kprobe_func;
	t_u64a	uprobe_path;
	t_u64a	config1;
}	t_linux_perf_bp_addr;

typedef union u_linux_perf_bp_len
{
	t_u64a	bp_len;
	t_u64a	kprobe_addr;
	t_u64a	probe_offset;
	t_u64a	config2;
}	t_linux_perf_bp_len;

typedef struct s_linux_perf_aux_action
{
	t_u32a	aux_start_paused : 1;
	t_u32a	aux_pause : 1;
	t_u32a	aux_resume : 1;
	t_u32a	reserved_3 : 29;
}	t_linux_perf_aux_action;

typedef union u_linux_perf_aux
{
	t_u32a						aux_action;
	t_linux_perf_aux_action		bits;
}	t_linux_perf_aux;

typedef struct s_perf_event_attr
{
	t_u32a					type;
	t_u32a					size;
	t_u64a					config;
	t_linux_perf_period		period;
	t_u64a					sample_type;
	t_u64a					read_format;
	t_u64a					disabled : 1;
	t_u64a					inherit : 1;
	t_u64a					pinned : 1;
	t_u64a					exclusive : 1;
	t_u64a					exclude_user : 1;
	t_u64a					exclude_kernel : 1;
	t_u64a					exclude_hv : 1;
	t_u64a					exclude_idle : 1;
	t_u64a					mmap : 1;
	t_u64a					comm : 1;
	t_u64a					freq : 1;
	t_u64a					inherit_stat : 1;
	t_u64a					enable_on_exec : 1;
	t_u64a					task : 1;
	t_u64a					watermark : 1;
	t_u64a					precise_ip : 2;
	t_u64a					mmap_data : 1;
	t_u64a					sample_id_all : 1;
	t_u64a					exclude_host : 1;
	t_u64a					exclude_guest : 1;
	t_u64a					exclude_callchain_kernel : 1;
	t_u64a					exclude_callchain_user : 1;
	t_u64a					mmap2 : 1;
	t_u64a					comm_exec : 1;
	t_u64a					use_clockid : 1;
	t_u64a					context_switch : 1;
	t_u64a					write_backward : 1;
	t_u64a					namespaces : 1;
	t_u64a					ksymbol : 1;
	t_u64a					bpf_event : 1;
	t_u64a					aux_output : 1;
	t_u64a					cgroup : 1;
	t_u64a					text_poke : 1;
	t_u64a					build_id : 1;
	t_u64a					inherit_thread : 1;
	t_u64a					remove_on_exec : 1;
	t_u64a					sigtrap : 1;
	t_u64a					reserved_1 : 26;
	t_linux_perf_wakeup		wakeup;
	t_u32a					bp_type;
	t_linux_perf_bp_addr	bp_addr;
	t_linux_perf_bp_len		bp_len;
	t_u64a					branch_sample_type;
	t_u64a					sample_regs_user;
	t_u32a					sample_stack_user;
	t_i32a					clockid;
	t_u64a					sample_regs_intr;
	t_u32a					aux_watermark;
	t_u16a					sample_max_stack;
	t_u16a					reserved_2;
	t_u32a					aux_sample_size;
	t_linux_perf_aux		aux;
	t_u64a					sig_data;
	t_u64a					config3;
}	t_perf_event_attr;

#  endif

int			xft_ioctl(int fd, t_u64a request, t_u64a arg);

int			xft_perf_event_open(const t_perf_event_attr *restrict attr,\
				int group_fd)\
				__attribute__((__nonnull__(1)));

# else

#  error "linux.h is linux only"

# endif
#endif
