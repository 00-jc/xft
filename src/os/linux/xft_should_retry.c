/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_should_retry.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/primitives.h>

#if defined(__linux__)

# include <xft/xft_p_syscalls.h>

__attribute__((const, __always_inline__, __used__))
inline bool	xft_should_retry(t_result res)
{
	return (res.err == xft_err_retry || res.err == xft_err_wouldblock);
}

#endif
