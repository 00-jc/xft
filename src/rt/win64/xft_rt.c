/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_rt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 22:38:36 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 15:41:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(_WIN64) && !defined(XFT_REQUIRE_LIBC) && !defined(XFT_NO_RT)

__attribute__((noreturn))
void	_start(void)
{
	xft_main((const t_any *)__builtin_frame_address(0));
}

#endif
