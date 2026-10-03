/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_rt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 15:40:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(__linux__) && !defined(XFT_REQUIRE_LIBC)\
	&& defined(__aarch64__) && !defined(XFT_NO_RT)

__attribute__((naked, noreturn))
void	_start(void)
{
	__asm__(
		"mov x29, #0\n"
		"mov x0, sp\n"
		"and x1, x0, #-16\n"
		"mov sp, x1\n"
		"bl xft_main\n"
		"brk #1\n"
		);
}

#endif
