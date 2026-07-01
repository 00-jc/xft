/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if !defined(FT_REQUIRE_LIBC) && defined(__x86_64__)

__attribute__((noreturn, force_align_arg_pointer))
void	_start(void)
{
	t_u64a		argc;
	t_u8		**argv;
	t_u8		**envp;
	void		**sp;

	__asm__(
		"mov %%rsp, %0"
		:"=r"(sp)
		::"memory"
		);
	argc = ((t_u64 *)sp)[0];
	argv = (t_u8 **)(sp + 1);
	envp = argv + argc + 1;
	ft_exit(ft_main(argc, argv, envp));
	__builtin_unreachable();
}

#elif defined(FT_REQUIRE_LIBC)

int	main(int argc, char **argv, char **envp)
{
	return (ft_main((t_u64a)argc, (t_u8 **)argv, (t_u8 **)envp));
}

#endif
