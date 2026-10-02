/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_kernel_ptrs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:38:36 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 15:57:11 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "shell32.lib")

#if defined(_WIN64) && !defined(XFT_NO_RT)

__attribute__((__nonnull__(1), __hot__, __always_inline__, __used__))
inline t_kernel_ptrs	xft_get_kernel_ptrs(const t_any *__restrict__ const sp)
{
	t_kernel_ptrs	kp;
	int				argc;
	LPWSTR			cmd;

	(void)sp;
	cmd = GetCommandLineW();
	kp.argv = (const t_nat_str **)CommandLineToArgvW(cmd, &argc);
	kp.argc = (t_size)argc;
	kp.envp = (const t_nat_str *)GetEnvironmentStringsW();
	return (kp);
}

#endif
