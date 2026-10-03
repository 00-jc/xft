/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_lockf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 14:41:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <stdbool.h>

t_i32a	xft_lockf(int fd)
{
	bool					result;
	OVERLAPPED				ov;

	ov = (OVERLAPPED){0};
	result = LockFileEx((HANDLE)(intptr_t)fd, LOCKFILE_EXCLUSIVE_LOCK, 0,
			MAXDWORD, MAXDWORD, &ov);
	return ((t_i32a)xft_tern(result, 0, (t_u64a)-1));
}

t_i32a	xft_unlockf(int fd)
{
	bool					result;
	OVERLAPPED				ov;

	ov = (OVERLAPPED){0};
	result = UnlockFileEx((HANDLE)(intptr_t)fd, 0, MAXDWORD, MAXDWORD, &ov);
	return ((t_i32a)xft_tern(result, 0, (t_u64a)-1));
}

#endif
