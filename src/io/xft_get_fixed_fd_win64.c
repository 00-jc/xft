/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_fixed_fd_win64.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

#ifdef _WIN64

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__always_inline__, __used__))
inline t_i32	xft_get_stdin(void)
{
	return ((t_i32)(intptr_t)GetStdHandle(STD_INPUT_HANDLE));
}

__attribute__((__always_inline__, __used__))
inline t_i32	xft_get_stdout(void)
{
	return ((t_i32)(intptr_t)GetStdHandle(STD_OUTPUT_HANDLE));
}

__attribute__((__always_inline__, __used__))
inline t_i32	xft_get_stderr(void)
{
	return ((t_i32)(intptr_t)GetStdHandle(STD_ERROR_HANDLE));
}

#endif
