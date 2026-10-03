/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__cold__, __always_inline__, __noreturn__, __used__))
inline void	xft_exit(int status)
{
	ExitProcess((UINT)status);
	__builtin_unreachable();
}

#endif
