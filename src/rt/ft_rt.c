/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 23:29:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if !defined(FT_REQUIRE_LIBC) && defined(__x86_64__)

__attribute__((noreturn, used, __nonnull__(1)))
inline void	ft_rt_entry(void **sp)
{
	t_u64a	argc;
	t_u8	**argv;
	t_u8	**envp;

	argc = ((t_u64 *)sp)[0];
	argv = (t_u8 **)(sp + 1);
	envp = argv + argc + 1;
	ft_exit(ft_main(argc, argv, envp));
	__builtin_unreachable();
}

__attribute__((naked, noreturn))
void	_start(void)
{
	__asm__(
		"xor %ebp, %ebp\n"
		"mov %rsp, %rdi\n"
		"and $-16, %rsp\n"
		"call ft_rt_entry\n"
		"hlt\n"
		);
}

#elif defined(FT_REQUIRE_LIBC)

int	main(int argc, char **argv, char **envp)
{
	return (ft_main((t_u64a)argc, (t_u8 **)argv, (t_u8 **)envp));
}

#endif
