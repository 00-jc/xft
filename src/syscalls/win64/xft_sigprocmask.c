/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sigprocmask.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:17:37 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 00:28:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "mem.h"
#include "types/signal_types.h"

#ifdef _WIN64

__attribute__((__always_inline__, __used__))
inline int	xft_sigprocmask(t_u32a flags, t_sigset *__restrict__ const set,
	t_sigset *__restrict__ const oldest)
{
	(void)flags;
	(void)set;
	if (oldest)
		xft_bzero(oldest, sizeof(*oldest));
	return (0);
}

#endif
