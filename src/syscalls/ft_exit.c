/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 15:26:21 by username          #+#    #+#             */
/*   Updated: 2026/06/28 15:27:04 by username         ###   ########.fr       */
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
