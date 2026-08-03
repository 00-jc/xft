/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:27:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/08 23:05:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_TYPES_H
# define SIGNAL_TYPES_H

# include "primitives.h"

/*
 *	rt_sigprocmask takes the mask size as a 4th argument and rejects
 *	anything but _NSIG/8 (8 on every 64-bit Linux). This is deliberately
 *	not sizeof(t_sigset): under FT_REQUIRE_LIBC that is glibc's 128-byte
 *	sigset_t, and passing 128 would get the call rejected with -EINVAL.
 *	Only the low 8 bytes are the kernel's mask, which is what glibc's
 *	own sigprocmask passes too.
 */
# define FT_SIGSET_SIZE	8

# if defined(FT_REQUIRE_LIBC) || (!defined(__x86_64__) && !defined(__aarch64__))

#  include <signal.h>

/// \brief Signal mask type: glibc's `sigset_t` (128 bytes) when built
/// against libc or on an arch without a raw syscall backend.
/// \note Only the first FT_SIGSET_SIZE (8) bytes are ever passed to the
/// kernel's rt_sigprocmask — the rest is libc's own bookkeeping.
typedef sigset_t	t_sigset;

# else

/// \brief Signal mask type for the freestanding raw-syscall backend: a
/// plain 64-bit bitmask, one bit per signal, matching the kernel's own
/// in-kernel sigset_t layout exactly (no glibc padding).
typedef t_u64a		t_sigset;

# endif

#endif
