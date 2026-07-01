/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"

#ifdef __x86_64__

__attribute__((__cold__, __always_inline__, __noreturn__))
inline void	ft_exit(int status)
{
	__asm__ volatile (
		"syscall"
		:
		: "a"(SYS_EXIT), "D"(status)
		: "rcx", "r11", "memory"
	);
	__builtin_unreachable();
}

#else

__attribute__((__cold__, __always_inline__, __noreturn__))
inline void	ft_exit(int status)
{
	syscall(SYS_EXIT, status);
	__builtin_unreachable();
}

#endif
