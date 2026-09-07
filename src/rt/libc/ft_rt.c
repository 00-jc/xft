/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined(FT_REQUIRE_LIBC) && !defined(FT_NO_RT)

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)envp;
	ft_main((const t_any *)((t_u64 *)argv - 1));
	__builtin_unreachable();
}

#endif
