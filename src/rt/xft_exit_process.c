/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_exit_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/27 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/rt.h>

#if defined(__linux__)
# include <xft/xft_p_syscalls.h>
#elif defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif

#if defined(__linux__)

__attribute__((__cold__, __always_inline__, __noreturn__, __used__))
inline void	xft_exit_process(t_i32a code)
{
	xft_exit_group(code);
}

#elif defined(_WIN32)

__attribute__((__cold__, __always_inline__, __noreturn__, __used__))
inline void	xft_exit_process(t_i32a code)
{
	ExitProcess((UINT)code);
	__builtin_unreachable();
}

#endif
