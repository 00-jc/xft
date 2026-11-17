/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_fixed_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/17 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>

#if defined(_WIN32)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

__attribute__((__always_inline__, __used__))
inline t_fd	xft_get_stdin(void)
{
	return ((t_fd)GetStdHandle(STD_INPUT_HANDLE));
}

__attribute__((__always_inline__, __used__))
inline t_fd	xft_get_stdout(void)
{
	return ((t_fd)GetStdHandle(STD_OUTPUT_HANDLE));
}

__attribute__((__always_inline__, __used__))
inline t_fd	xft_get_stderr(void)
{
	return ((t_fd)GetStdHandle(STD_ERROR_HANDLE));
}

#endif
