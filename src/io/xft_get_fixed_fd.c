/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_fixed_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/io.h>

#if defined(__linux__)

# include <xft/xft_p_syscalls.h>

__attribute__((const, __always_inline__, __used__))
inline t_i32	xft_get_stdin(void)
{
	return (xft_stdin_fileno);
}

__attribute__((const, __always_inline__, __used__))
inline t_i32	xft_get_stdout(void)
{
	return (xft_stdout_fileno);
}

__attribute__((const, __always_inline__, __used__))
inline t_i32	xft_get_stderr(void)
{
	return (xft_stderr_fileno);
}

#endif
