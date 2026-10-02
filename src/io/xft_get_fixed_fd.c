/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_get_fixed_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

#ifndef _WIN64

__attribute__((const, __always_inline__, __used__))
inline t_i32	xft_get_stdin(void)
{
	return (STDIN_FILENO);
}

__attribute__((const, __always_inline__, __used__))
inline t_i32	xft_get_stdout(void)
{
	return (STDOUT_FILENO);
}

__attribute__((const, __always_inline__, __used__))
inline t_i32	xft_get_stderr(void)
{
	return (STDERR_FILENO);
}

#endif
