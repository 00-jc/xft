/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 13:55:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include <limits.h>

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# pragma comment(lib, "kernel32.lib")
# include <stdbool.h>

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_ssize	xft_write(int fd, t_u8 *restrict const buffer, t_size len)
{
	bool	result;
	DWORD	written;
	t_size	clamp;

	written = 0;
	clamp = xft_tern(UINT32_MAX < len, UINT32_MAX, len);
	result = WriteFile((HANDLE)(intptr_t)fd, buffer,
			(DWORD)clamp, &written, (t_any)0);
	return (xft_tern(result, written, (t_u64)-1));
}

#endif
