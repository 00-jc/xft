/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_kernel_ptrs_destroy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:38:36 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 15:41:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(_WIN64)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__nonnull__(1)))
void	xft_kernel_ptrs_destroy(t_kernel_ptrs *kp)
{
	HeapFree(GetProcessHeap(), 0, (t_any)kp->argv);
	FreeEnvironmentStringsA((LPCH)kp->envp);
	kp->argc = 0;
	kp->argv = (t_any)0;
	kp->envp = (t_any)0;
}

#endif
