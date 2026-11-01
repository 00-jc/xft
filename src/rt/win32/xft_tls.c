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

ULONG						_tls_index = 0;

const IMAGE_TLS_DIRECTORY	_tls_used = {(ULONG_PTR) & g_tls_start,
	(ULONG_PTR) & g_tls_end, (ULONG_PTR) & _tls_index, 0, 0, 0};

#endif
