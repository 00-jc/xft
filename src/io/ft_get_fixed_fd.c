/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fixed_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

__attribute__((const, __always_inline__))
inline t_i32	ft_get_stdin(void)
{
	return (STDIN_FILENO);
}

__attribute__((const, __always_inline__))
inline t_i32	ft_get_stdout(void)
{
	return (STDOUT_FILENO);
}

__attribute__((const, __always_inline__))
inline t_i32	ft_get_stderr(void)
{
	return (STDERR_FILENO);
}
