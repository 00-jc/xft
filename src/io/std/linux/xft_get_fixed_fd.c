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

#if defined(__linux__)

# include <xft/xft_p_syscalls.h>

__attribute__((__const__, __always_inline__, __used__))
inline t_fd	xft_get_stdin(void)
{
	return (xft_stdin_fileno);
}

__attribute__((__const__, __always_inline__, __used__))
inline t_fd	xft_get_stdout(void)
{
	return (xft_stdout_fileno);
}

__attribute__((__const__, __always_inline__, __used__))
inline t_fd	xft_get_stderr(void)
{
	return (xft_stderr_fileno);
}

#endif
