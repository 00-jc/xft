/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_free_kernel_ptrs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:38:36 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 15:41:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(_WIN64) && !defined(XFT_NO_RT)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# pragma comment(lib, "kernel32.lib")

__attribute__((__nonnull__(1)))
void	xft_free_kernel_ptrs(t_kernel_ptrs *kp)
{
	if (kp->argv)
		LocalFree((HLOCAL)kp->argv);
	if (kp->envp)
		FreeEnvironmentStringsW((LPWCH)kp->envp);
	kp->argc = 0;
	kp->argv = (t_any)0;
	kp->envp = (t_any)0;
}

#endif
