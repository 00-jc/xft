/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 14:44:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <stdbool.h>

__attribute__((__always_inline__, __used__))
inline int	xft_close(int fd)
{
	bool	result;

	result = CloseHandle((HANDLE)(intptr_t)fd);
	return ((int)xft_tern(result, 0, (t_u64a)-1));
}

#endif
