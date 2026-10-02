/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 14:04:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"

#ifdef _WIN64

# include <windows.h>
# include <stdbool.h>

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline int	xft_mkdir(const char *restrict path, t_u32a mode)
{
	bool					result;

	(void)mode;
	result = CreateDirectoryA((t_any)path, (t_any)0);
	return ((int)xft_tern(result, 0, (t_u64)-1));
}

#endif
