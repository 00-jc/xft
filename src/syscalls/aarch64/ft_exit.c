/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 12:49:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"

#ifdef __aarch64__

__attribute__((__cold__, __always_inline__, __noreturn__))
inline void	ft_exit(int status)
{
	const register long x8	__asm__("x8") = SYS_EXIT;
	const register long x0	__asm__("x0") = status;

	__asm__ volatile (
		"svc #0"
		:
		: "r"(x8), "r"(x0)
		: "memory", "cc"
	);
	__builtin_unreachable();
}

#endif
