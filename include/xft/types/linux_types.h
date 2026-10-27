/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINUX_TYPES_H
# define LINUX_TYPES_H

# ifdef __linux__
#  include <xft/primitives.h>
#  ifdef XFT_REQUIRE_LIBC
#   include <linux/perf_event.h>
#  endif

typedef enum e_xft_perf_type : t_u8
{
	xft_perf_type_hardware = 0,
	xft_perf_type_software = 1,
}	t_xft_perf_type;

typedef enum e_xft_perf_hw : t_u8
{
	xft_perf_count_hw_cpu_cycles = 0,
	xft_perf_count_hw_instructions = 1,
	xft_perf_count_hw_cache_ll = 2,
	xft_perf_count_hw_cache_misses = 3,
	xft_perf_count_hw_branch_instructions = 4,
	xft_perf_count_hw_branch_misses = 5,
}	t_xft_perf_hw;

typedef enum e_xft_perf_sw : t_u8
{
	xft_perf_count_sw_page_faults = 2,
	xft_perf_count_sw_alignment_faults = 7,
	xft_perf_count_sw_dummy = 9,
}	t_xft_perf_sw;

typedef enum e_xft_perf_format : t_u8
{
	xft_perf_format_total_time_enabled = 0x01,
	xft_perf_format_total_time_running = 0x02,
	xft_perf_format_group = 0x08,
}	t_xft_perf_format;

typedef enum e_xft_perf_flag : t_u8
{
	xft_perf_flag_fd_cloexec = 0x08,
}	t_xft_perf_flag;

typedef enum e_xft_perf_ioc : t_u16
{
	xft_perf_ioc_flag_group = 0x01,
	xft_perf_event_ioc_enable = 0x2400,
	xft_perf_event_ioc_disable = 0x2401,
	xft_perf_event_ioc_reset = 0x2403,
}	t_xft_perf_ioc;

#  ifdef XFT_REQUIRE_LIBC

typedef struct perf_event_attr	t_perf_event_attr;

#  else

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

# else

#  error "linux.h is linux only"

# endif
#endif
