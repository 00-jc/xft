/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_tls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/rt.h>

#if defined(_WIN32) && !defined(XFT_REQUIRE_LIBC) && !defined(XFT_NO_RT)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((section(".tls")))
static char g_tls_start = 0;

__attribute__((section(".tls$ZZZ")))
static char g_tls_end = 0;

# ifdef __i386__

ULONG g_tls_index						__asm__("__tls_index") = 0;

const IMAGE_TLS_DIRECTORY g_tls_used	__asm__("__tls_used") = {
	(ULONG_PTR) & g_tls_start,
	(ULONG_PTR) & g_tls_end, (ULONG_PTR) & g_tls_index, 0, 0, 0};

# else

ULONG g_tls_index						__asm__("_tls_index") = 0;

const IMAGE_TLS_DIRECTORY g_tls_used	__asm__("_tls_used") = {
	(ULONG_PTR) & g_tls_start,
	(ULONG_PTR) & g_tls_end, (ULONG_PTR) & g_tls_index, 0, 0, 0};

# endif

#endif
