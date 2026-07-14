/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mprotect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 09:54:35 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/08 09:58:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_syscalls.h"
#include "syscalls.h"

#ifdef __x86_64__

__attribute__((__nonnull__(1)))
int	ft_mprotect(t_any addr, t_size size, int prot)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_MPROTECT),
		"D"(addr),
		"S"(size),
		"d"(prot)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

#endif
