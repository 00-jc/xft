/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/14 00:53:58 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef FT_REQUIRE_LIBC

__attribute__((__nonnull__(1), __always_inline__))
inline t_i32	ft_clone(const t_clone_arg *__restrict__ const args)
{
	return ((t_i32)syscall(SYS_CLONE, args->flags, args->stack,
			args->ptid, args->ctid, args->tls));
}

#endif
