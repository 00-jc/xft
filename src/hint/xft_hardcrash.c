/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_hardcrash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 13:45:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_hint.h>
#include <xft/io.h>

#if defined(__linux__)
# include <xft/xft_p_syscalls.h>
#elif defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif

#if defined(__linux__)

__attribute__((__noreturn__, __cold__, __noinline__))
void	xft_hardcrash_with_message(t_buffer msg)
{
	if (msg.mem == nullptr)
		__builtin_unreachable();
	xft_write(xft_get_stderr(), msg.mem, msg.size);
	xft_exit_group(1);
}

__attribute__((__noreturn__, __cold__, __noinline__))
void	xft_hardcrash(void)
{
	xft_exit_group(1);
}

#elif defined(_WIN32)

__attribute__((__noreturn__, __cold__, __noinline__))
void	xft_hardcrash_with_message(t_buffer msg)
{
	DWORD	n;

	if (msg.mem == nullptr)
		__builtin_unreachable();
	WriteFile((HANDLE)(intptr_t)xft_get_stderr(), msg.mem, (DWORD)msg.size,
		&n, nullptr);
	ExitProcess(1);
}

__attribute__((__noreturn__, __cold__, __noinline__))
void	xft_hardcrash(void)
{
	ExitProcess(1);
}

#endif
