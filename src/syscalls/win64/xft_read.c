/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 14:41:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <stdbool.h>

__attribute__((__nonnull__(2), __always_inline__, __used__))
inline t_ssize	xft_read(int fd, t_u8 *restrict const buffer, t_size len)
{
	t_size	clamp;
	DWORD	read;
	bool	result;

	read = 0;
	clamp = xft_tern(UINT32_MAX < len, UINT32_MAX, len);
	result = ReadFile((HANDLE)(intptr_t)fd, (t_any)buffer, (DWORD)clamp,
			&read, (t_any)0);
	return (xft_tern(result || GetLastError() == ERROR_BROKEN_PIPE,
			read, (t_u64)-1));
}

#endif
