/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_kernel_ptrs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:38:36 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/22 04:10:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_rt.h>
#include <xft/hint.h>
#include <xft/mem.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <shellapi.h>

__attribute__((__nonnull__(1), __hot__, __always_inline__, __used__))
inline t_kernel_ptrs	xft_get_kernel_ptrs(const t_any *__restrict__ const sp)
{
	t_kernel_ptrs	kp;
	LPWSTR			*w;
	t_u8			*s;
	int				size;
	int				i;

	(void)sp;
	w = CommandLineToArgvW(GetCommandLineW(), &i);
	xft_pin_invariant_msg(w != nullptr, xft_fatptr((t_u8 *)"no argv\n", 8));
	kp.argc = (t_size)i;
	kp.envp = (const t_nat_str *)GetEnvironmentStringsA();
	size = (i + 1) * (int)(sizeof(t_u8 *));
	while (i-- > 0)
		size += 3 * lstrlenW(w[i]) + 1;
	kp.argv = HeapAlloc(GetProcessHeap(), 0, (t_size)size);
	xft_pin_invariant_msg(kp.argv && kp.envp, xft_fatptr((t_u8 *)"oom\n", 4));
	s = (t_u8 *)(kp.argv + kp.argc + 1);
	while (++i < (int)kp.argc)
	{
		kp.argv[i] = s;
		s += WideCharToMultiByte(CP_UTF8, 0, w[i], -1, (LPSTR)s, size, 0, 0);
	}
	kp.argv[i] = nullptr;
	LocalFree((HLOCAL)w);
	return (kp);
}

#endif
