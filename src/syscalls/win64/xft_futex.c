/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_futex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 21:04:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 00:27:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "types/atomic_types.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

LONG	RtlWaitOnAddress(volatile void *addr, void *cmp, SIZE_T size,
			LARGE_INTEGER *timeout);
void	RtlWakeAddressSingle(void *addr);
void	RtlWakeAddressAll(void *addr);

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_i64a	xft_futex_wait(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	LONG	status;

	status = RtlWaitOnAddress(uaddr, &val, sizeof(val), (t_any)0);
	return ((t_i64a)xft_tern(status < 0, (t_u64a)-1, 0));
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_i64a	xft_futex_wake(t_u32a *__restrict__ const uaddr, t_u32a val)
{
	if (val == 1)
		RtlWakeAddressSingle(uaddr);
	else if (val)
		RtlWakeAddressAll(uaddr);
	return (0);
}

#endif
