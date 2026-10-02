/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_rt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 15:40:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(__linux__) && !defined(XFT_REQUIRE_LIBC) \
	&& defined(__x86_64__) && !defined(XFT_NO_RT)

__attribute__((naked, noreturn))
void	_start(void)
{
	__asm__(
		"xor %ebp, %ebp\n"
		"mov %rsp, %rdi\n"
		"and $-16, %rsp\n"
		"call xft_main\n"
		"hlt\n"
		);
}

#endif
