/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_sysinfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 22:45:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/28 22:45:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_rt.h>
#include <xft/os.h>
#include <xft/bmi.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <bcrypt.h>

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_sysinfo	xft_get_sysinfo(const t_any *__restrict__ sp)
{
	static t_u8	random[16];
	SYSTEM_INFO	si;
	ULONG_PTR	stack[2];
	t_sysinfo	info;
	t_size		cpus;

	(void)sp;
	GetSystemInfo(&si);
	GetCurrentThreadStackLimits(&stack[0], &stack[1]);
	cpus = 1;
	xft_get_cpu_count(&cpus);
	info.random = (t_any)xft_tern_s(BCryptGenRandom(nullptr, random,
				sizeof(random), BCRYPT_USE_SYSTEM_PREFERRED_RNG) >= 0,
			(t_uptr)random, 0);
	info.page_size = si.dwPageSize;
	info.stack_size = stack[1] - stack[0];
	info.cpu_count = (t_u32a)cpus;
	info.cache_line_size = xft_cache_line_size();
	return (info);
}

#endif
