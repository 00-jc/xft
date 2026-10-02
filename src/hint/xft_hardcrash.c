/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_hardcrash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 13:45:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_hint.h"
#include "io.h"
#include "syscalls.h"

__attribute__((__noreturn__, __cold__, __noinline__))
void	xft_hardcrash_with_message(t_buffer msg)
{
	if (msg.mem == nullptr)
		__builtin_unreachable();
	xft_write(xft_get_stderr(), msg.mem, msg.size);
	xft_exit(1);
}

__attribute__((__noreturn__, __cold__, __noinline__))
void	xft_hardcrash(void)
{
	xft_exit(1);
}
