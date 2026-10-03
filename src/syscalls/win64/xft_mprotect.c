/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mprotect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 09:54:35 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/08 09:58:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <stdbool.h>

__attribute__((__always_inline__, const, unused, __used__))
inline DWORD	xft_p_mprotect_prot(int prot)
{
	DWORD	acc;

	acc = PAGE_NOACCESS;
	acc = (DWORD)xft_tern(prot & PROT_READ, PAGE_READONLY, acc);
	acc = (DWORD)xft_tern(prot & PROT_WRITE, PAGE_READWRITE, acc);
	acc <<= xft_tern(prot & PROT_EXEC, 4, 0);
	return (acc);
}

__attribute__((__nonnull__(1)))
int	xft_mprotect(t_any addr, t_size size, int prot)
{
	DWORD	old;
	bool	result;

	result = VirtualProtect(addr, size, xft_p_mprotect_prot(prot), &old);
	return ((int)xft_tern(result, 0, (t_u64a)-1));
}

#endif
