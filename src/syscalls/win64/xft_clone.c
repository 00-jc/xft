/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_clone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 00:28:42 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline t_i32	xft_clone(const t_clone_arg *__restrict__ const args)
{
	(void)args;
	SetLastError(ERROR_NOT_SUPPORTED);
	return (-1);
}

#endif
