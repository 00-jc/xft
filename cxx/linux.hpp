/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:31:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 16:31:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINUX_HPP
# define LINUX_HPP

# include "c.hpp"

namespace xft
{
/* named linux_ rather than linux: some toolchains predefine a bare
 * `linux` macro to 1 in non-strict GNU modes, which would expand this
 * to "namespace 1" and fail to compile; the trailing underscore sidesteps
 * that landmine entirely, the same way goto_() sidesteps the goto
 * keyword in tokenizer.hpp. */
namespace linux_
{

/* linux.h defines the Linux perf_event ABI: either t_perf_event_attr is
 * pulled in verbatim from <linux/perf_event.h> (FT_REQUIRE_LIBC), or it
 * is xft's own freestanding redefinition of the same layout, together
 * with the PERF_* constants below (which match the UAPI header's names
 * exactly either way). t_perf_event_attr and t_linux_perf_* are
 * module-owned, not primitives, but there are no functions declared in
 * this header at all and they are plain configuration data with no
 * lifetime of their own (built once, handed to a syscall), so there is
 * no class here to attach a c::-qualified type to - unlike syscalls.hpp's
 * perf_event_open, which does reach c::t_perf_event_attr directly. The
 * constants are exposed as namespaced values instead, the same treatment
 * as elf.hpp's AT_* macros. */

static const t_u32a	perf_type_hardware = PERF_TYPE_HARDWARE;
static const t_u32a	perf_type_software = PERF_TYPE_SOFTWARE;

static const t_u64a	perf_count_hw_cpu_cycles = PERF_COUNT_HW_CPU_CYCLES;
static const t_u64a	perf_count_hw_instructions = PERF_COUNT_HW_INSTRUCTIONS;
static const t_u64a	perf_count_hw_cache_ll = PERF_COUNT_HW_CACHE_LL;
static const t_u64a	perf_count_hw_cache_misses = PERF_COUNT_HW_CACHE_MISSES;
static const t_u64a	perf_count_hw_branch_instructions
	= PERF_COUNT_HW_BRANCH_INSTRUCTIONS;
static const t_u64a	perf_count_hw_branch_misses = PERF_COUNT_HW_BRANCH_MISSES;

static const t_u64a	perf_count_sw_page_faults = PERF_COUNT_SW_PAGE_FAULTS;
static const t_u64a	perf_count_sw_alignment_faults
	= PERF_COUNT_SW_ALIGNMENT_FAULTS;
static const t_u64a	perf_count_sw_dummy = PERF_COUNT_SW_DUMMY;

static const t_u32a	perf_format_total_time_enabled
	= PERF_FORMAT_TOTAL_TIME_ENABLED;
static const t_u32a	perf_format_total_time_running
	= PERF_FORMAT_TOTAL_TIME_RUNNING;
static const t_u32a	perf_format_group = PERF_FORMAT_GROUP;

static const unsigned long	perf_flag_fd_cloexec = PERF_FLAG_FD_CLOEXEC;

static const int	perf_ioc_flag_group = PERF_IOC_FLAG_GROUP;
static const int	perf_event_ioc_enable = PERF_EVENT_IOC_ENABLE;
static const int	perf_event_ioc_disable = PERF_EVENT_IOC_DISABLE;
static const int	perf_event_ioc_reset = PERF_EVENT_IOC_RESET;

}
}

#endif
