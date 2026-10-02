/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_rt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(XFT_REQUIRE_LIBC) && !defined(XFT_NO_RT)

# if defined(_WIN64)

int	main(void)
{
	xft_main((const t_any *)__builtin_frame_address(0));
	__builtin_unreachable();
}

# else

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)envp;
	xft_main((const t_any *)((t_u64 *)argv - 1));
	__builtin_unreachable();
}

# endif

#endif
